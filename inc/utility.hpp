#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <tuple>

// Base case: stop recursion when there are no arguments
bool isNULL()
{
  return false;
}

// variadic template
template <typename T, typename... Args>
bool isNULL(T first, Args... args)
{
  if (first != nullptr)
  {
    return isNULL(args...); // recursive call
  }
  else
  {
    return true;
  }
}


// Termination conditions for recursive calls
template <typename GstElement>
bool linkElementsHelper(GstElement *source, GstElement *last)
{
  // Base case: Only two elements, link them directly.
  return gst_element_link(source, last);
}

// Auxiliary structure for recursively linking elements
template <typename First, typename Second, typename... Rest>
bool linkElementsHelper(First *first, Second *second, Rest *...rest)
{
  // Recursive case: Link the adjacent elements and call itself recursively for the rest.
  return gst_element_link(first, second) && linkElementsHelper(second, rest...);
}

// The outermost linkElements function is used to start recursion
template <typename... GstElementTypes>
bool linkElements(GstElementTypes *...elements)
{
  // External interface that calls the helper function.
  return linkElementsHelper(elements...); // Fold Expressions Template
}
#endif