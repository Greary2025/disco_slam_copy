#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Generate a relative transform (4x4) file in fast_gicp's relative.txt format
from two pose text files (target and source) that contain:

index\n<N>\ntimestamp\n<T>\nx\n<X>\ny\n<Y>\nz\n<Z>\nqx\n<QX>\nqy\n<QY>\nqz\n<QZ>\nqw\n<QW>

The output transform is T_target_source = T_world_target * inv(T_world_source),
which maps source frame points into the target frame (matching fast_gicp tests).

This script can be run without arguments; paths are hardcoded below.
"""
import os
import sys
from typing import Dict

import math


def _read_pose_txt(path: str) -> Dict[str, float]:
    # Robust simple parser for the provided key-value per line format
    if not os.path.isfile(path):
        raise FileNotFoundError(f"Pose file not found: {path}")

    keys = {
        'index', 'timestamp', 'x', 'y', 'z', 'qx', 'qy', 'qz', 'qw'
    }
    data: Dict[str, float] = {}
    with open(path, 'r', encoding='utf-8') as f:
        lines = [ln.strip() for ln in f if ln.strip()]
    i = 0
    while i < len(lines):
        key = lines[i]
        if key in keys and i + 1 < len(lines):
            try:
                val = float(lines[i + 1])
            except ValueError:
                # index may be integer; store as float for uniformity
                try:
                    val = float(int(lines[i + 1]))
                except ValueError:
                    raise ValueError(f"Invalid numeric value for {key} in {path}: {lines[i+1]}")
            data[key] = val
            i += 2
        else:
            # Skip unknown tokens gracefully
            i += 1

    required = ['x', 'y', 'z', 'qx', 'qy', 'qz', 'qw']
    for r in required:
        if r not in data:
            raise ValueError(f"Missing required field '{r}' in {path}")
    return data


def _quat_to_R(qx: float, qy: float, qz: float, qw: float):
    # Normalize quaternion to be safe
    n = math.sqrt(qx*qx + qy*qy + qz*qz + qw*qw)
    if n == 0.0:
        raise ValueError("Zero-norm quaternion")
    qx, qy, qz, qw = qx/n, qy/n, qz/n, qw/n

    # Rotation matrix from unit quaternion (w,x,y,z) -> using (qx,qy,qz,qw)
    xx = qx*qx; yy = qy*qy; zz = qz*qz
    xy = qx*qy; xz = qx*qz; yz = qy*qz
    wx = qw*qx; wy = qw*qy; wz = qw*qz

    R = [
        [1 - 2*(yy + zz),     2*(xy - wz),       2*(xz + wy)],
        [2*(xy + wz),         1 - 2*(xx + zz),   2*(yz - wx)],
        [2*(xz - wy),         2*(yz + wx),       1 - 2*(xx + yy)]
    ]
    return R


def _mat_inv(R, t):
    # Inverse of SE3: [R t; 0 1]^-1 = [R^T, -R^T t; 0 1]
    Rt = [[R[0][0], R[1][0], R[2][0]],
          [R[0][1], R[1][1], R[2][1]],
          [R[0][2], R[1][2], R[2][2]]]
    tx = -(Rt[0][0]*t[0] + Rt[0][1]*t[1] + Rt[0][2]*t[2])
    ty = -(Rt[1][0]*t[0] + Rt[1][1]*t[1] + Rt[1][2]*t[2])
    tz = -(Rt[2][0]*t[0] + Rt[2][1]*t[1] + Rt[2][2]*t[2])
    return Rt, [tx, ty, tz]


def _mat_mul(Ra, ta, Rb, tb):
    # Compose SE3: [Ra ta]*[Rb tb] = [Ra Rb, Ra tb + ta]
    Rc = [[0.0]*3 for _ in range(3)]
    for i in range(3):
        for j in range(3):
            Rc[i][j] = Ra[i][0]*Rb[0][j] + Ra[i][1]*Rb[1][j] + Ra[i][2]*Rb[2][j]
    tc = [
        Ra[0][0]*tb[0] + Ra[0][1]*tb[1] + Ra[0][2]*tb[2] + ta[0],
        Ra[1][0]*tb[0] + Ra[1][1]*tb[1] + Ra[1][2]*tb[2] + ta[1],
        Ra[2][0]*tb[0] + Ra[2][1]*tb[1] + Ra[2][2]*tb[2] + ta[2],
    ]
    return Rc, tc


def _write_relative_txt(path: str, R, t):
    # Write as 4 lines with spaces, similar to example
    with open(path, 'w', encoding='utf-8') as f:
        f.write(f"{R[0][0]:.6f}    {R[0][1]:.6f} {R[0][2]:.6f}     {t[0]:.6f}\n")
        f.write(f"  {R[1][0]:.6f}     {R[1][1]:.6f}  {R[1][2]:.6f}      {t[1]:.6f}\n")
        f.write(f" {R[2][0]:.6f}   {R[2][1]:.6f}     {R[2][2]:.6f}   {t[2]:.6f}\n")
        f.write(f"           0            0            0            1\n")


def compute_and_write(target_txt: str, source_txt: str, out_dir: str, out_name: str) -> str:
    tgt = _read_pose_txt(target_txt)
    src = _read_pose_txt(source_txt)

    Rt = _quat_to_R(tgt['qx'], tgt['qy'], tgt['qz'], tgt['qw'])
    tt = [tgt['x'], tgt['y'], tgt['z']]

    Rs = _quat_to_R(src['qx'], src['qy'], src['qz'], src['qw'])
    ts = [src['x'], src['y'], src['z']]

    # T_rel = T_w_t * inv(T_w_s)
    Rs_inv, ts_inv = _mat_inv(Rs, ts)
    Rrel, trel = _mat_mul(Rt, tt, Rs_inv, ts_inv)

    os.makedirs(out_dir, exist_ok=True)
    out_path = os.path.join(out_dir, out_name)
    _write_relative_txt(out_path, Rrel, trel)
    return out_path


def main(argv=None):
    # Hardcoded parameters: modify these as needed
    TARGET_TXT = "/home/john/gicp_test/src/fast_gicp/data/synchronous_xianfeng/00075.txt"
    SOURCE_TXT = "/home/john/gicp_test/src/fast_gicp/data/synchronous_xianfeng/01031.txt"
    OUT_DIR    = "/home/john/gicp_test/src/fast_gicp/data/synchronous_xianfeng"
    OUT_NAME   = "relative_from_00075_01031.txt"

    try:
        print("Generating relative transform with:")
        print(f"  target: {TARGET_TXT}")
        print(f"  source: {SOURCE_TXT}")
        print(f"  out_dir: {OUT_DIR}")
        print(f"  out_name: {OUT_NAME}")
        out_path = compute_and_write(TARGET_TXT, SOURCE_TXT, OUT_DIR, OUT_NAME)
        print(f"Done. Written relative transform to: {out_path}")
        return 0
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        return 1


if __name__ == '__main__':
    sys.exit(main())
