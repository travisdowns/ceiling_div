#ifndef ALLX_H
#define ALLX_H

#define X_MACRO(x_func)	  \
  x_func(divide_chris)	\
  x_func(divide_dummy) \
  /* x_func(divide_questionc) .. fails at (0x80..., 2)	*/	\
  x_func(divide_weather)				\
  x_func(divide_chux) \
  x_func(divide_user23) \
  x_func(divide_user23_variant) \
  x_func(divide_chrisdodd) \
  x_func(divide_plusq)

#define STRING(a) #a,
#define STRING32(a) #a "_32"
const char * const algo_names[]   = { X_MACRO(STRING) };
const char * const algo_names32[] = { X_MACRO(STRING32) };
const unsigned algo_count = sizeof(algo_names) / sizeof(algo_names[0]);


#endif // ALLX_H
