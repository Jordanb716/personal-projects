#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>

//Constants
const int WIDTH = 800;
const int HEIGHT = 600;

class HelloTriangleApplication {
public:
	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

private:

	//Variables
	GLFWwindow* window;
	VkInstance instance;

	//Functions
	void initWindow() {

		glfwInit(); //Initialize GLFW library.
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //No OpenGL context.
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //Disable resizing window. (Too complex for now)
		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr); //Create window.

	}

	void initVulkan() {

		createInstance(); //Create Vulkan instance.

	}

	void createInstance() {

		VkApplicationInfo appInfo = {};

		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo = {};

		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionsCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);

		createInfo.enabledExtensionCount = glfwExtensionsCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		createInfo.enabledLayerCount = 0;

		VkResult result = vkCreateInstance(&createInfo, nullptr, &instance); //Create instance.

		if (result != VK_SUCCESS) {
			throw std::runtime_error("Failed to create instance!");
		}

	}

	void mainLoop() {

		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}

	}

	void cleanup() {

		vkDestroyInstance(instance, nullptr);

		glfwDestroyWindow(window); //Clean up window.

		glfwTerminate(); //Close GLFW library.

	}

};

int main() {
	HelloTriangleApplication app;

	try {
		app.run();
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}