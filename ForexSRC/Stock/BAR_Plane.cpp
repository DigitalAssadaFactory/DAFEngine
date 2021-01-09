#include "BAR_Plane.h"



namespace Stock {
	/*
	BAR_Plane::BAR_Plane(const std::vector<Candle>& bars, const int& from,
		const int& length, const int& depth, const int& periodStride)
	{
		if (from - length < 0) Logger::ThrowBox("BAR_Plane:\nInvalid range.");

		m_data = DYNAMIC_ARRAY_02_INIT(float, 0, 0);

		for (size_t i = from; i <= from + length; ++i)
		{
			m_data.push_back(std::vector<float>(0));
			for (size_t j = 0; j < depth; ++j)
			{
				if ((from - length - 1 - j * periodStride) < 0) break;
				m_data[i - from].push_back( bars[ i + (i-(from-length)) * j ].m_close );
			}
		}
	}

	void BAR_Plane::LoadGraphics()
	{
		for (size_t i = 0; i < m_data.size() - 1; ++i)
		{
			for (size_t j = 0; j < m_data[0].size() - 1; ++j)
			{
				m_quads.push_back(
					Quad(
						Vertex(i * scaleX, m_data[i][j + 1] * scaleY, j * scaleZ + scaleZ),
						Vertex(i * scaleX + scaleX, m_data[i + 1][j + 1] * scaleY, j * scaleZ + scaleZ),
						Vertex(i * scaleX, m_data[i][j] * scaleY, j * scaleZ),
						Vertex(i * scaleX + scaleX, m_data[i + 1][j] * scaleY, j * scaleZ)
						)
					);
			}
		}

		using namespace ECS;
		using namespace ECS::Component;
		for (auto& q : m_quads)
		{
			Entity e;
			e.AddComponent<Mesh>();
			e.AddComponent<Renderer>();

			auto _mesh = e.GetComponent<Mesh>();
			auto _rend = e.GetComponent<Renderer>();

			_mesh.vertices = q.vertices;
			_mesh.indices = q.indices;
			_rend.drawMode = DM::SingleSolid;
			_rend.vertexShader = VS::Default;
			_rend.pixelShader = PS::Default;

			m_entities.push_back(std::move(e));
		}

		for (auto& e : m_entities) System::Graphics::AddModel(e);
	}
	*/
}