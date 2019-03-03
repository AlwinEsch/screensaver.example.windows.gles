/*
 *      Copyright (C) 2019 Team Kodi
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this Program; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include <kodi/gui/gl/GL.h>
#include <kodi/gui/gl/Shader.h>
#include <kodi/addon-instance/Screensaver.h>

class ATTRIBUTE_HIDDEN CExampleTriangle
  : public kodi::addon::CAddonBase,
    public kodi::addon::CInstanceScreensaver,
    public kodi::gui::gl::CShaderProgram
{
public:
  CExampleTriangle() = default;

  // override functions for kodi::addon::CInstanceScreensaver
  bool Start() override;
  void Stop() override;
  void Render() override;

  // override functions for kodi::gui::gl::CShaderProgram
  void OnCompiledAndLinked() override;
  bool OnEnabled() override { return true;  }

private:
  GLuint m_vertexVBO = 0;
  GLint m_aPosition = -1;
  GLint m_aColor = -1;
};

bool CExampleTriangle::Start()
{
  std::string fraqShader = kodi::GetAddonPath("resources/shaders/" GL_TYPE_STRING "/glsl.frag");
  std::string vertShader = kodi::GetAddonPath("resources/shaders/" GL_TYPE_STRING "/glsl.vert");
  if (!LoadShaderFiles(vertShader, fraqShader) || !CompileAndLink())
    return false;

  glGenBuffers(1, &m_vertexVBO);
  return true;
}

void CExampleTriangle::Stop()
{
  glDeleteBuffers(1, &m_vertexVBO);
  m_vertexVBO = 0;
}

void CExampleTriangle::Render()
{
  const struct PackedVertex {
    float position[3]; // Position x, y, z
    float color[4]; // Color r, g, b, a
  } vertices[3] = {
    { { -0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
    { {  0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
    { {  0.0f,  0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
  };

  glVertexAttribPointer(m_aPosition, 3, GL_FLOAT, GL_FALSE, sizeof(PackedVertex), BUFFER_OFFSET(offsetof(PackedVertex, position)));
  glEnableVertexAttribArray(m_aPosition);

  glVertexAttribPointer(m_aColor, 4, GL_FLOAT, GL_FALSE, sizeof(PackedVertex), BUFFER_OFFSET(offsetof(PackedVertex, color)));
  glEnableVertexAttribArray(m_aColor);

  EnableShader();
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  DisableShader();
}

void CExampleTriangle::OnCompiledAndLinked()
{
  m_aPosition = glGetAttribLocation(ProgramHandle(), "a_position");
  m_aColor = glGetAttribLocation(ProgramHandle(), "a_color");
}

ADDONCREATOR(CExampleTriangle);
