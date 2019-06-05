#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*
Shader Pipeline
https://heinleinsgame.tistory.com/7?category=757483

[1.] Vertex Shader
 - 로컬좌표 월드좌표 변환.
 - 정점 속성에 대한 기본적인 처리.
 - 정점 속성(vertex attributes) : 위치, 컬러 등..
 - vertex buffer objects(VBO)로 정점 데이터 메모리 관리.

2. Shape Assembly(Primitive assembly)
 - 정점으로부터 도형을 만든다.
 - primitive : 정점의 렌더링 정보를 나타냄.

3. Geometry shader
 - 정점집합 -> 새로운 도형 생성.

4. Rasterization
 - primitive를 최종 화면의 픽셀과 매핑.
 - fragment 가 도출됨.
 - Cliping 수행.(가려진 fragment 폐기)

[5.] Fragment Shader
- 픽셀의 최종 컬러 계산.
- 고급 기능 사용.

6. Alpha tests and Blending
 - fragment의 깊이와 스텐실을 체크.
 - 투명도에 따라 블렌딩.
*/

class VertexShader
{
public:
	unsigned int VBO;

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};


public:
	void CreateVertex()
	{
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		
		// GL_STATIC_DRAW : 데이터가 거의 변하지 않습니다.
		// GL_DYNAMIC_DRAW: 데이터가 자주 변경됩니다.
		// GL_STREAM_DRAW : 데이터가 그려질때마다 변경됩니다.
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}
};