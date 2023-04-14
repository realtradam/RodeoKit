
#define mrodeo_name_concat(prefix, suffix) prefix##suffix

#define mrodeo_macrovar(prefix) mrodeo_name_concat(prefix##_, __LINE__)

#define mrodeo_defer_do(start, end)						\
	for(												\
		int mrodeo_macrovar(_macrovar_) = (start, 0);	\
		!mrodeo_macrovar(_macrovar_);					\
		(mrodeo_macrovar(_macrovar_) += 1), end			\
	)													\

#define								\
mrodeo_vargs_do(final_arg)			\
	va_list vargs;					\
	mrodeo_defer_do(				\
		va_start(vargs, final_arg),	\
		va_end(vargs)				\
	)								\

