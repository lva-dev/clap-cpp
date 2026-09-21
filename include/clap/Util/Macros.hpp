#pragma once

#ifndef CLAP_CONFIG_DEBUG
	#ifdef NDEBUG
		#define CLAP_CONFIG_RELEASE
	#else
		#define CLAP_CONFIG_DEBUG
	#endif
#endif