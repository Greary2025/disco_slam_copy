from setuptools import find_packages
from setuptools import setup

setup(
    name='disco_slam',
    version='1.0.0',
    packages=find_packages(
        include=('disco_slam', 'disco_slam.*')),
)
