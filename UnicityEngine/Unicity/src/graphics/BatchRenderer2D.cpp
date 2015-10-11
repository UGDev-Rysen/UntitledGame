#include <graphics/BatchRenderer2D.h>
#include <shaders/ShaderFactory.h>
#include <graphics/MeshFactory.h>

namespace u_engine { namespace graphics {

	BatchRenderer2D::BatchRenderer2D(const maths::tvec2<UE_uint>& screenSize) 
	: m_IndexCount(0), m_ScreenSize(screenSize), m_ViewportSize(screenSize) {

		init();
	}

	BatchRenderer2D::~BatchRenderer2D() {

		delete m_IBO;
		GLCall(glDeleteBuffers(1, &m_VBO));
		GLCall(glDeleteVertexArrays(1, &m_VAO));
	}

	UE_void BatchRenderer2D::init() {

		GLCall(glGenVertexArrays(1, &m_VAO));
		GLCall(glGenBuffers(1, &m_VBO));
		
		GLCall(glBindVertexArray(m_VAO));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
		GLCall(glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW));
		
		GLCall(glEnableVertexAttribArray(SHADER_VERTEX_INDEX));
		GLCall(glEnableVertexAttribArray(SHADER_UV_INDEX));
		GLCall(glEnableVertexAttribArray(SHADER_MASK_UV_INDEX));
		GLCall(glEnableVertexAttribArray(SHADER_TID_INDEX));
		GLCall(glEnableVertexAttribArray(SHADER_MID_INDEX));
		GLCall(glEnableVertexAttribArray(SHADER_COLOR_INDEX));
		
		GLCall(glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0));
		GLCall(glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv))));
		GLCall(glVertexAttribPointer(SHADER_MASK_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, mask_uv))));
		GLCall(glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, tid))));
		GLCall(glVertexAttribPointer(SHADER_MID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, mid))));
		GLCall(glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, color))));
		
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

		GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];

		UE_int offset = 0;
		for (UE_int i = 0; i < RENDERER_INDICES_SIZE; i += 6) {

			indices[  i  ] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}


		m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

		GLCall(glBindVertexArray(0));

		//Setup FrameBuffer

		GLCall(glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_ScreenBuffer));
		m_FrameBuffer = new Framebuffer(m_ViewportSize);
		m_SimpleShader = ShaderFactory::SimpleShader();
		m_SimpleShader->bind();
		m_SimpleShader->setUniformMat4("pr_matrix", maths::mat4::orthographic(0, m_ScreenSize.x, m_ScreenSize.y, 0, -1.0f, 1.0f));
		m_SimpleShader->setUniform1i("tex", 0);
		m_SimpleShader->unbind();
		m_ScreenQuad = MeshFactory::CreateQuad(0, 0, m_ScreenSize.x, m_ScreenSize.y);

		m_PostEffects = new PostEffects();
		m_PostEffectsBuffer = new Framebuffer(m_ViewportSize);

	}

	UE_float BatchRenderer2D::submitTexture(UE_uint textureID) {

		UE_float result = 0.0f;
		UE_bool found = false;
		for (UE_uint i = 0; i < m_TextureSlots.size(); i++) {

			if (m_TextureSlots[i] == textureID) {

				result = (UE_float)(i + 1);
				found = true;
				break;
			}
		}

		if (!found) {

			if (m_TextureSlots.size() >= RENDERER_MAX_TEXTURES) {

				end();
				flush();
				begin();
			}
			m_TextureSlots.push_back(textureID);
			result = (UE_float)(m_TextureSlots.size());
		}
		return result;
	}


	UE_float BatchRenderer2D::submitTexture(const Texture* texture) {

		return submitTexture(texture->getID());
	}


	UE_void BatchRenderer2D::begin() {

		if (m_Target == RenderTarget::BUFFER) {

			if (m_ViewportSize != m_FrameBuffer->GetSize()) {

				delete m_FrameBuffer;
				m_FrameBuffer = new Framebuffer(m_ViewportSize);

				if (m_PostEffectsEnabled) {
                    
					delete m_PostEffectsBuffer;
					m_PostEffectsBuffer = new Framebuffer(m_ViewportSize);
				}
			}

			if (m_PostEffectsEnabled) {

				m_PostEffectsBuffer->Bind();
				m_PostEffectsBuffer->Clear();
			}

			m_FrameBuffer->Bind();
			m_FrameBuffer->Clear();
		} else {
			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_ScreenBuffer));
			GLCall(glViewport(0, 0, m_ScreenSize.x, m_ScreenSize.y));


		}




		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
		GLCall(m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	}

	UE_void BatchRenderer2D::submit(const Renderable2D* renderable) {

		const maths::vec3& position = renderable->getPosition();
		const maths::vec2& size = renderable->getSize();
		const UE_uint color = renderable->getColor();
		const std::vector<maths::vec2>& uv = renderable->getUV();

		const GLuint tid = renderable->getTID();

		
		UE_float ts = 0.0f;
		if (tid > 0)
			ts = submitTexture(renderable->getTexture());

		maths::mat4 maskTransform = maths::mat4::identity();
		const GLuint mid = m_Mask ? m_Mask->texture->getID() : 0;
		UE_float ms = 0.0f;

		if (m_Mask != nullptr) {

			maskTransform = maths::mat4::invert(m_Mask->transform);
			ms = submitTexture(m_Mask->texture);
		}

		
		maths::vec3 vertex = *m_TransformationBack * position;
		m_Buffer->vertex = vertex;
		m_Buffer->uv = uv[0];
		m_Buffer->mask_uv = maskTransform * vertex;
		m_Buffer->tid = ts;
		m_Buffer->mid = ms;
		m_Buffer->color = color;
		m_Buffer++;

		vertex = *m_TransformationBack * maths::vec3(position.x, position.y + size.y, position.z);
		m_Buffer->vertex = vertex;
		m_Buffer->uv = uv[1];
		m_Buffer->mask_uv = maskTransform * vertex;
		m_Buffer->tid = ts;
		m_Buffer->mid = ms;
		m_Buffer->color = color;
		m_Buffer++;

		vertex = *m_TransformationBack * maths::vec3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->vertex = vertex;
		m_Buffer->uv = uv[2];
		m_Buffer->mask_uv = maskTransform * vertex;
		m_Buffer->tid = ts;
		m_Buffer->mid = ms;
		m_Buffer->color = color;
		m_Buffer++;

		vertex = *m_TransformationBack * maths::vec3(position.x + size.x, position.y, position.z);
		m_Buffer->vertex = vertex;
		m_Buffer->uv = uv[3];
		m_Buffer->mask_uv = maskTransform * vertex;
		m_Buffer->tid = ts;
		m_Buffer->mid = ms;
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;

	}


	UE_void BatchRenderer2D::drawString(const UE_string& text, const maths::vec3& position, const Font& font, UE_uint color) {

		using namespace ftgl;

		


		UE_float ts = 0.0f;
		ts = submitTexture(font.getID());

			const maths::vec2& scale = font.getScale();

			UE_float x = position.x;

			texture_font_t* ftFont = font.getFTFont();

			for (UE_uint i = 0; i < text.length(); i++) {

				UE_char c = text[i];
				texture_glyph_t* glyph = texture_font_get_glyph(ftFont, c);
				if (glyph != NULL) {

					if (i > 0) {

						UE_float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
						x += kerning / scale.x;
					}

					UE_float x0 = x + glyph->offset_x / scale.x;
					UE_float y0 = position.y + glyph->offset_y / scale.y;
					UE_float x1 = x0 + glyph->width / scale.x;
					UE_float y1 = y0 - glyph->height / scale.x;
					
					UE_float u0 = glyph->s0;
					UE_float v0 = glyph->t0;
					UE_float u1 = glyph->s1;
					UE_float v1 = glyph->t1;
					
					m_Buffer->vertex = *m_TransformationBack * maths::vec3(x0, y0, 0);
					m_Buffer->uv = maths::vec2(u0, v0);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;
					
					m_Buffer->vertex = *m_TransformationBack * maths::vec3(x0, y1, 0);
					m_Buffer->uv = maths::vec2(u0, v1);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;
					
					m_Buffer->vertex = *m_TransformationBack * maths::vec3(x1, y1, 0);
					m_Buffer->uv = maths::vec2(u1, v1);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;
					
					m_Buffer->vertex = *m_TransformationBack * maths::vec3(x1, y0, 0);
					m_Buffer->uv = maths::vec2(u1, v0);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;
					
					m_IndexCount += 6;
					
					x += glyph->advance_x / scale.x;
				}
			}

		

	}


	UE_void BatchRenderer2D::end() {

		GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	UE_void BatchRenderer2D::flush() {

		for (UE_uint i = 0; i < m_TextureSlots.size(); i++) {

			GLCall(glActiveTexture(GL_TEXTURE0 + i));
			glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
		}

		

		GLCall(glBindVertexArray(m_VAO));
		m_IBO->bind();

		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

		m_IBO->unbind();
		GLCall(glBindVertexArray(0));

		m_IndexCount = 0;
		m_TextureSlots.clear();

		if (m_Target == RenderTarget::BUFFER) {

        //Post Effects pass should go here //TODO//
			if (m_PostEffectsEnabled)
				m_PostEffects->RenderPostEffects(m_FrameBuffer, m_PostEffectsBuffer, m_ScreenQuad, m_IBO);

			//Display framebuffer - potentially move to FB class
			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_ScreenBuffer));
			GLCall(glViewport(0, 0, m_ScreenSize.x, m_ScreenSize.y));
			m_SimpleShader->bind();

			GLCall(glActiveTexture(GL_TEXTURE0));
			m_FrameBuffer->GetTexture()->bind();

			if (m_PostEffectsEnabled)
				m_PostEffectsBuffer->GetTexture()->bind();
			else
				m_FrameBuffer->GetTexture()->bind();

			GLCall(glBindVertexArray(m_ScreenQuad));
			m_IBO->bind();

			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
			m_IBO->unbind();

			GLCall(glBindVertexArray(0));
			m_SimpleShader->unbind();
		}


	}

} }