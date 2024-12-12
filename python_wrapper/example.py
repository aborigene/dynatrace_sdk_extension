import ctypes

# Load the shared library
oneagent = ctypes.CDLL('./liboneagent_wrapper.so')

# Initialize the OneAgent SDK
def initialize_oneagent():
    result = oneagent.initialize_oneagent()
    if result != 0:
        raise Exception("OneAgent SDK initialization failed")

# Shutdown the OneAgent SDK
def shutdown_oneagent():
    oneagent.shutdown_oneagent()

def simple_trace():
    oneagent.simple_trace()

initialize_oneagent()
simple_trace()
print("tracing!")
shutdown_oneagent()