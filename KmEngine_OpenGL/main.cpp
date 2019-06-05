#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main(int argc, char* argv[])
{
// GLFW 초기화
	glfwInit();
	// GLFW 설정
	// https://www.glfw.org/docs/latest/window.html#window_hints 참고.
	// GLFW 에게 OpenGL 3.3 을 사용한다고 알려줌.
	// 사용자가 적절한 OPenGL 버전을 가지고 있지 않을 때, GLFW 가 실행되지 않는다.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// 윈도우 생성
	const int	width  = 800;
	const int	height = 600;
	GLFWwindow* window = glfwCreateWindow(width, height, "KmEngine_OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window [main.cpp/18]" << std::endl;
		glfwTerminate();
		return -1;
	}
	// 이 window의 context를 현재 스레드의 주 context로 지정하겠다고 GLFW에게 알려줌.
	glfwMakeContextCurrent(window);

// GLAD 초기화
	// GLAD -> OpenGL용 함수 포인터를 관리.
	// 따라서 OpenGL의 함수들을 호출하기 전에 초기화해야함.
	// GLFW -> 컴파일 환경 OS에 따라 올바른 함수를 정의하는 glfwGetProcAddress 를 제공.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD [main.cpp/33]" << std::endl;
		return -1;
	}
	
// OpenGL에 렌더링 사이즈 지시
	// OpenGL은 glViewport함수를 통해 2D좌표를 스크린 좌표로 변환함.
	// OpenGL 좌표는 -1~1사이이므로, 이를 스크린 픽셀 좌표로 매핑함.
	glViewport(0, 0, width, height);
	// 윈도우 사이즈가 변경(사용자에 의해 조정) 되는 순간 뷰표트 조정을 위해 콜백함수를 호출한다.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

// Engine 준비
	// Render loop.
	// 종료 메세지를 받기 전까지 루프함.
	while (!glfwWindowShouldClose(window))	// 각 루프가 시작될 때마다 GLFW 종료지시를 받았는지 확인.
	{
	// ESC로 종료.
		processInput(window);

	// 렌더링
		// 컬러버퍼 색상 지정 (state-setting function)
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// 화면 컬러 버퍼를 클리어 (state-using function)
		glClear(GL_COLOR_BUFFER_BIT);

	// 더블버퍼링
		glfwSwapBuffers(window);
	// 이벤트(키입력, 마우스이동 등..)발생여부 확인, 윈도우 상태 업데이트, 콜백함수 호출.
		glfwPollEvents();			
	}

// 종료. 자원정리.
	glfwTerminate();
	return 0;
}

// resize 콜백함수.
// 창 크기 조정되는 순간의 뷰포트를 조정.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// 입력관리 함수
void processInput(GLFWwindow* window)
{
	// ESC 로 윈도우 종료.
	// 안눌려졌다면, GLFW_RELEASE를 리턴한다.
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}