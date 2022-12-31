#pragma once

#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"

namespace test
{
	class TestAdvancedGLSL : public Test
	{
	public:
		TestAdvancedGLSL();
		~TestAdvancedGLSL();

		void OnUpdate(float deltaTime) override;
		void OnRender(Camera& camera) override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_CubeVAO;
		std::unique_ptr<VertexBuffer> m_CubeVBO;
		std::unique_ptr<Shader> m_ShaderRed;
		std::unique_ptr<Shader> m_ShaderGreen;
		std::unique_ptr<Shader> m_ShaderBlue;
		std::unique_ptr<Shader> m_ShaderYellow;
		uint32_t m_UBOMatrices;
	};
}
