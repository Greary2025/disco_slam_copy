// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from disco_slam:msg/CloudInfo.idl
// generated code does not contain a copyright notice

#ifndef DISCO_SLAM__MSG__DETAIL__CLOUD_INFO__FUNCTIONS_H_
#define DISCO_SLAM__MSG__DETAIL__CLOUD_INFO__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "disco_slam/msg/rosidl_generator_c__visibility_control.h"

#include "disco_slam/msg/detail/cloud_info__struct.h"

/// Initialize msg/CloudInfo message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * disco_slam__msg__CloudInfo
 * )) before or use
 * disco_slam__msg__CloudInfo__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
bool
disco_slam__msg__CloudInfo__init(disco_slam__msg__CloudInfo * msg);

/// Finalize msg/CloudInfo message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
void
disco_slam__msg__CloudInfo__fini(disco_slam__msg__CloudInfo * msg);

/// Create msg/CloudInfo message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * disco_slam__msg__CloudInfo__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
disco_slam__msg__CloudInfo *
disco_slam__msg__CloudInfo__create();

/// Destroy msg/CloudInfo message.
/**
 * It calls
 * disco_slam__msg__CloudInfo__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
void
disco_slam__msg__CloudInfo__destroy(disco_slam__msg__CloudInfo * msg);

/// Check for msg/CloudInfo message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
bool
disco_slam__msg__CloudInfo__are_equal(const disco_slam__msg__CloudInfo * lhs, const disco_slam__msg__CloudInfo * rhs);

/// Copy a msg/CloudInfo message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
bool
disco_slam__msg__CloudInfo__copy(
  const disco_slam__msg__CloudInfo * input,
  disco_slam__msg__CloudInfo * output);

/// Initialize array of msg/CloudInfo messages.
/**
 * It allocates the memory for the number of elements and calls
 * disco_slam__msg__CloudInfo__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
bool
disco_slam__msg__CloudInfo__Sequence__init(disco_slam__msg__CloudInfo__Sequence * array, size_t size);

/// Finalize array of msg/CloudInfo messages.
/**
 * It calls
 * disco_slam__msg__CloudInfo__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
void
disco_slam__msg__CloudInfo__Sequence__fini(disco_slam__msg__CloudInfo__Sequence * array);

/// Create array of msg/CloudInfo messages.
/**
 * It allocates the memory for the array and calls
 * disco_slam__msg__CloudInfo__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
disco_slam__msg__CloudInfo__Sequence *
disco_slam__msg__CloudInfo__Sequence__create(size_t size);

/// Destroy array of msg/CloudInfo messages.
/**
 * It calls
 * disco_slam__msg__CloudInfo__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
void
disco_slam__msg__CloudInfo__Sequence__destroy(disco_slam__msg__CloudInfo__Sequence * array);

/// Check for msg/CloudInfo message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
bool
disco_slam__msg__CloudInfo__Sequence__are_equal(const disco_slam__msg__CloudInfo__Sequence * lhs, const disco_slam__msg__CloudInfo__Sequence * rhs);

/// Copy an array of msg/CloudInfo messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
bool
disco_slam__msg__CloudInfo__Sequence__copy(
  const disco_slam__msg__CloudInfo__Sequence * input,
  disco_slam__msg__CloudInfo__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // DISCO_SLAM__MSG__DETAIL__CLOUD_INFO__FUNCTIONS_H_
