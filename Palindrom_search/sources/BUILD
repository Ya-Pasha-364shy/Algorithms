cc_library(
	name = "palindrom_search_fsm_lib",
	srcs = ["palindrom_srch.cpp"],
	hdrs = ["palindrom_srch.hpp"],

	visibility = ["//visibility:public"],
)

cc_binary(
	name = "palindrom-search-fsm",
	srcs = ["palindrom_srch.cpp"],

	deps = [
		":palindrom_search_fsm_lib",
	],
)

