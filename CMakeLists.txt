set(COMPONENT_SRCS 
		"src/jbkernel/Console.cpp"
		"src/jbkernel/CriticalSections.c"
		"src/jbkernel/EventTimer.cpp"
		"src/jbkernel/EventTimerOneTime.cpp"
		"src/jbkernel/IVoidMemory.cpp"
		"src/jbkernel/JbKernel.cpp"
		"src/jbkernel/JbKernelFreeRtos.cpp"
		"src/jbkernel/JbTftpServer.cpp"
		"src/jbkernel/KernelPerformer.cpp"
		"src/jbkernel/TimeEngine.cpp"
		"src/jbkernel/VoidChannelMsgQueue.cpp"
		"src/jbkernel/ZingerServer.cpp")
set(COMPONENT_ADD_INCLUDEDIRS 
		"include")
		
set(COMPONENT_REQUIRES jblib-platform-abstract-jbutilities main)

register_component()