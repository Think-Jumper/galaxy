if (MSVC)
	set(GALAXY_LINK_FLAGS
		/SAFESEH
        /ignore:4099
        /MACHINE:X64
	)

	set(GALAXY_LINK_FLAGS_DEBUG
		${GALAXY_LINK_FLAGS}
		/INCREMENTAL
        /DEBUG
        /SUBSYSTEM:CONSOLE
	)

	set(GALAXY_LINK_FLAGS_RELEASE
		${GALAXY_LINK_FLAGS}
		/INCREMENTAL:NO
        /SUBSYSTEM:WINDOWS
        /OPT:REF
        /OPT:ICF
        /LTCG:incremental
	)
else()
	set(GALAXY_LINK_FLAGS
		-pthread
		-static
		-static-libgcc
		-static-libstdc++
	)

	set(GALAXY_LINK_FLAGS_DEBUG
		${GALAXY_LINK_FLAGS}
	)

	set(GALAXY_LINK_FLAGS_RELEASE
		${GALAXY_LINK_FLAGS}
	)
endif()