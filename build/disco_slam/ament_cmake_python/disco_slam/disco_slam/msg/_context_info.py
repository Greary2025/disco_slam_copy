# generated from rosidl_generator_py/resource/_idl.py.em
# with input from disco_slam:msg/ContextInfo.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'scan_context_bin'
# Member 'ring_key'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ContextInfo(type):
    """Metaclass of message 'ContextInfo'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('disco_slam')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'disco_slam.msg.ContextInfo')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__context_info
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__context_info
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__context_info
            cls._TYPE_SUPPORT = module.type_support_msg__msg__context_info
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__context_info

            from sensor_msgs.msg import PointCloud2
            if PointCloud2.__class__._TYPE_SUPPORT is None:
                PointCloud2.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ContextInfo(metaclass=Metaclass_ContextInfo):
    """Message class 'ContextInfo'."""

    __slots__ = [
        '_robot_id',
        '_robot_id_receive',
        '_header',
        '_num_ring',
        '_num_sector',
        '_pose_x',
        '_pose_y',
        '_pose_z',
        '_pose_roll',
        '_pose_pitch',
        '_pose_yaw',
        '_pose_intensity',
        '_scan_cloud',
        '_scan_context_bin',
        '_ring_key',
    ]

    _fields_and_field_types = {
        'robot_id': 'string',
        'robot_id_receive': 'string',
        'header': 'std_msgs/Header',
        'num_ring': 'int64',
        'num_sector': 'int64',
        'pose_x': 'float',
        'pose_y': 'float',
        'pose_z': 'float',
        'pose_roll': 'float',
        'pose_pitch': 'float',
        'pose_yaw': 'float',
        'pose_intensity': 'float',
        'scan_cloud': 'sensor_msgs/PointCloud2',
        'scan_context_bin': 'sequence<float>',
        'ring_key': 'sequence<float>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('int64'),  # noqa: E501
        rosidl_parser.definition.BasicType('int64'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['sensor_msgs', 'msg'], 'PointCloud2'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.robot_id = kwargs.get('robot_id', str())
        self.robot_id_receive = kwargs.get('robot_id_receive', str())
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.num_ring = kwargs.get('num_ring', int())
        self.num_sector = kwargs.get('num_sector', int())
        self.pose_x = kwargs.get('pose_x', float())
        self.pose_y = kwargs.get('pose_y', float())
        self.pose_z = kwargs.get('pose_z', float())
        self.pose_roll = kwargs.get('pose_roll', float())
        self.pose_pitch = kwargs.get('pose_pitch', float())
        self.pose_yaw = kwargs.get('pose_yaw', float())
        self.pose_intensity = kwargs.get('pose_intensity', float())
        from sensor_msgs.msg import PointCloud2
        self.scan_cloud = kwargs.get('scan_cloud', PointCloud2())
        self.scan_context_bin = array.array('f', kwargs.get('scan_context_bin', []))
        self.ring_key = array.array('f', kwargs.get('ring_key', []))

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.robot_id != other.robot_id:
            return False
        if self.robot_id_receive != other.robot_id_receive:
            return False
        if self.header != other.header:
            return False
        if self.num_ring != other.num_ring:
            return False
        if self.num_sector != other.num_sector:
            return False
        if self.pose_x != other.pose_x:
            return False
        if self.pose_y != other.pose_y:
            return False
        if self.pose_z != other.pose_z:
            return False
        if self.pose_roll != other.pose_roll:
            return False
        if self.pose_pitch != other.pose_pitch:
            return False
        if self.pose_yaw != other.pose_yaw:
            return False
        if self.pose_intensity != other.pose_intensity:
            return False
        if self.scan_cloud != other.scan_cloud:
            return False
        if self.scan_context_bin != other.scan_context_bin:
            return False
        if self.ring_key != other.ring_key:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def robot_id(self):
        """Message field 'robot_id'."""
        return self._robot_id

    @robot_id.setter
    def robot_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'robot_id' field must be of type 'str'"
        self._robot_id = value

    @builtins.property
    def robot_id_receive(self):
        """Message field 'robot_id_receive'."""
        return self._robot_id_receive

    @robot_id_receive.setter
    def robot_id_receive(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'robot_id_receive' field must be of type 'str'"
        self._robot_id_receive = value

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def num_ring(self):
        """Message field 'num_ring'."""
        return self._num_ring

    @num_ring.setter
    def num_ring(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'num_ring' field must be of type 'int'"
            assert value >= -9223372036854775808 and value < 9223372036854775808, \
                "The 'num_ring' field must be an integer in [-9223372036854775808, 9223372036854775807]"
        self._num_ring = value

    @builtins.property
    def num_sector(self):
        """Message field 'num_sector'."""
        return self._num_sector

    @num_sector.setter
    def num_sector(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'num_sector' field must be of type 'int'"
            assert value >= -9223372036854775808 and value < 9223372036854775808, \
                "The 'num_sector' field must be an integer in [-9223372036854775808, 9223372036854775807]"
        self._num_sector = value

    @builtins.property
    def pose_x(self):
        """Message field 'pose_x'."""
        return self._pose_x

    @pose_x.setter
    def pose_x(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'pose_x' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'pose_x' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._pose_x = value

    @builtins.property
    def pose_y(self):
        """Message field 'pose_y'."""
        return self._pose_y

    @pose_y.setter
    def pose_y(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'pose_y' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'pose_y' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._pose_y = value

    @builtins.property
    def pose_z(self):
        """Message field 'pose_z'."""
        return self._pose_z

    @pose_z.setter
    def pose_z(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'pose_z' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'pose_z' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._pose_z = value

    @builtins.property
    def pose_roll(self):
        """Message field 'pose_roll'."""
        return self._pose_roll

    @pose_roll.setter
    def pose_roll(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'pose_roll' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'pose_roll' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._pose_roll = value

    @builtins.property
    def pose_pitch(self):
        """Message field 'pose_pitch'."""
        return self._pose_pitch

    @pose_pitch.setter
    def pose_pitch(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'pose_pitch' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'pose_pitch' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._pose_pitch = value

    @builtins.property
    def pose_yaw(self):
        """Message field 'pose_yaw'."""
        return self._pose_yaw

    @pose_yaw.setter
    def pose_yaw(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'pose_yaw' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'pose_yaw' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._pose_yaw = value

    @builtins.property
    def pose_intensity(self):
        """Message field 'pose_intensity'."""
        return self._pose_intensity

    @pose_intensity.setter
    def pose_intensity(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'pose_intensity' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'pose_intensity' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._pose_intensity = value

    @builtins.property
    def scan_cloud(self):
        """Message field 'scan_cloud'."""
        return self._scan_cloud

    @scan_cloud.setter
    def scan_cloud(self, value):
        if __debug__:
            from sensor_msgs.msg import PointCloud2
            assert \
                isinstance(value, PointCloud2), \
                "The 'scan_cloud' field must be a sub message of type 'PointCloud2'"
        self._scan_cloud = value

    @builtins.property
    def scan_context_bin(self):
        """Message field 'scan_context_bin'."""
        return self._scan_context_bin

    @scan_context_bin.setter
    def scan_context_bin(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'scan_context_bin' array.array() must have the type code of 'f'"
            self._scan_context_bin = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'scan_context_bin' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._scan_context_bin = array.array('f', value)

    @builtins.property
    def ring_key(self):
        """Message field 'ring_key'."""
        return self._ring_key

    @ring_key.setter
    def ring_key(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'ring_key' array.array() must have the type code of 'f'"
            self._ring_key = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'ring_key' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._ring_key = array.array('f', value)
