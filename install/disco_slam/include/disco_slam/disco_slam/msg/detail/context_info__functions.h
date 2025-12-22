// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from disco_slam:msg/ContextInfo.idl
// generated code does not contain a copyright notice

#ifndef DISCO_SLAM__MSG__DETAIL__CONTEXT_INFO__FUNCTIONS_H_
#define DISCO_SLAM__MSG__DETAIL__CONTEXT_INFO__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "disco_slam/msg/rosidl_generator_c__visibility_control.h"

#include "disco_slam/msg/detail/context_info__struct.h"

/// Initialize msg/ContextInfo message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * disco_slam__msg__ContextInfo
 * )) before or use
 * disco_slam__msg__ContextInfo__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
bool
disco_slam__msg__ContextInfo__init(disco_slam__msg__ContextInfo * msg);

/// Finalize msg/ContextInfo message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
void
disco_slam__msg__ContextInfo__fini(disco_slam__msg__ContextInfo * msg);

/// Create msg/ContextInfo message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * disco_slam__msg__ContextInfo__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
disco_slam__msg__ContextInfo *
disco_slam__msg__ContextInfo__create();

/// Destroy msg/ContextInfo message.
/**
 * It calls
 * disco_slam__msg__ContextInfo__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
void
disco_slam__msg__ContextInfo__destroy(disco_slam__msg__ContextInfo * msg);

/// Check for msg/ContextInfo message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
bool
disco_slam__msg__ContextInfo__are_equal(const disco_slam__msg__ContextInfo * lhs, const disco_slam__msg__ContextInfo * rhs);

/// Copy a msg/ContextInfo message.
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
disco_slam__msg__ContextInfo__copy(
  const disco_slam__msg__ContextInfo * input,
  disco_slam__msg__ContextInfo * output);

/// Initialize array of msg/ContextInfo messages.
/**
 * It allocates the memory for the number of elements and calls
 * disco_slam__msg__ContextInfo__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
bool
disco_slam__msg__ContextInfo__Sequence__init(disco_slam__msg__ContextInfo__Sequence * array, size_t size);

/// Finalize array of msg/ContextInfo messages.
/**
 * It calls
 * disco_slam__msg__ContextInfo__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
void
disco_slam__msg__ContextInfo__Sequence__fini(disco_slam__msg__ContextInfo__Sequence * array);

/// Create array of msg/ContextInfo messages.
/**
 * It allocates the memory for the array and calls
 * disco_slam__msg__ContextInfo__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
disco_slam__msg__ContextInfo__Sequence *
disco_slam__msg__ContextInfo__Sequence__create(size_t size);

/// Destroy array of msg/ContextInfo messages.
/**
 * It calls
 * disco_slam__msg__ContextInfo__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
void
disco_slam__msg__ContextInfo__Sequence__destroy(disco_slam__msg__ContextInfo__Sequence * array);

/// Check for msg/ContextInfo message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_disco_slam
bool
disco_slam__msg__ContextInfo__Sequence__are_equal(const disco_slam__msg__ContextInfo__Sequence * lhs, const disco_slam__msg__ContextInfo__Sequence * rhs);

/// Copy an array of msg/ContextInfo messages.
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
disco_slam__msg__ContextInfo__Sequence__copy(
  const disco_slam__msg__ContextInfo__Sequence * input,
  disco_slam__msg__ContextInfo__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // DISCO_SLAM__MSG__DETAIL__CONTEXT_INFO__FUNCTIONS_H_
