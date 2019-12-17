#include "aepch.h"
#include "Shader.h"

#include <Anomaly/Rendering/stb_image.h>
#include <glad/glad.h>

namespace Anomaly
{
	Shader::Shader(const char* VertexSrcFileName, const char* FragmentSrcFileName, const char* geometryPath)
	{
		ReadInShaders(VertexSrcFileName, FragmentSrcFileName, geometryPath);
		
		// Create an empty vertex shader handle
		const GLchar *source = static_cast<const GLchar *>(VertexSrc.c_str());
		GLint isCompiled = 0;
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		{
			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			
			glShaderSource(vertexShader, 1, &source, nullptr);
			
			// Compile the vertex shader
			glCompileShader(vertexShader);
			CheckComplied(vertexShader, "VERTEX");

		}
		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		{
			// Send the fragment shader source code to GL
			source = static_cast<const GLchar *>(FragmentSrc.c_str());
			glShaderSource(fragmentShader, 1, &source, 0);
			
			// Compile the fragment shader
			glCompileShader(fragmentShader);	
			CheckComplied(vertexShader, "FRAGMENT");
		}
		// Create an empty geometry shader handle
		GLuint GeomShader = glCreateShader(GL_GEOMETRY_SHADER);
		{
			// Send the Geom shader source code to GL
			if(geometryPath != nullptr)
			{
				source = static_cast<const GLchar *>(GeomSrc.c_str());
				glShaderSource(GeomShader, 1, &source, 0);			
				// Compile the fragment shader
				glCompileShader(GeomShader);
				CheckComplied(vertexShader, "GEOMETRY");
				
			}	
		}

		// Vertex, fragment and geom shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();
		
		// Attach our shaders to our program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);
		if(geometryPath != nullptr)
			glAttachShader(m_RendererID, GeomShader);
		
		// Link our program
		glLinkProgram(m_RendererID);
		CheckComplied(m_RendererID, "PROGRAM");
		
		// Always detach shaders after a successful link.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		if(geometryPath != nullptr)
			glDeleteShader(GeomShader);

	}
	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}
	void Shader::UnBind() const
	{
		glUseProgram(0);
	}

	void Shader::ReadInShaders(const char* VertexSrcFileName, const char* FragmentSrcFileName, const char* geometrySrcFileName)
	{
		//Vertex Shader
		{
			std::string AppPathVert = __argv[0];	
			AppPathVert.replace(AppPathVert.end() - 11, AppPathVert.end(), "Shaders\\" + std::string(VertexSrcFileName));
			const char* vPath = AppPathVert.c_str();

			std::ifstream VertexShaderFile;
			VertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			
			try
			{		
				VertexShaderFile.open(vPath);
				
				std::stringstream ShaderStreamVert;
				ShaderStreamVert << VertexShaderFile.rdbuf();		
				VertexSrc = ShaderStreamVert.str();
				
				VertexShaderFile.close();
			}
			catch (std::ifstream::failure e)
			{
				AE_CORE_ERROR("Vertex Shader File failed to read!: {0}", e.what());
			}
		}

		//Fragment Shader
		{
			std::string AppPathFrag = __argv[0];
			AppPathFrag.replace(AppPathFrag.end() - 11, AppPathFrag.end(), "Shaders\\" + std::string(FragmentSrcFileName));
			const char* fPath = AppPathFrag.c_str();
			
			std::stringstream ShaderStreamFrag;
			std::ifstream FragmentShaderFile;
			FragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try
			{			
				FragmentShaderFile.open(fPath);
				ShaderStreamFrag << FragmentShaderFile.rdbuf();
				FragmentSrc = ShaderStreamFrag.str();
				FragmentShaderFile.close();
			}
			catch (std::ifstream::failure e)
			{
				AE_CORE_ERROR("Fragment Shader File failed to read!: {0}", e.what());
			}
		}
		
		//Geom Shader
		{
			if(geometrySrcFileName != nullptr)
			{
				std::string AppPathGeom = __argv[0];
				AppPathGeom.replace(AppPathGeom.end() - 11, AppPathGeom.end(), "Shaders\\" + std::string(geometrySrcFileName));
				const char* gPath = AppPathGeom.c_str();
				
				std::stringstream ShaderStreamGeom;
				std::ifstream GeomShaderFile;
				GeomShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				try
				{
					GeomShaderFile.open(gPath);
					ShaderStreamGeom << GeomShaderFile.rdbuf();
					GeomSrc = ShaderStreamGeom.str();
					GeomShaderFile.close();
				}
				catch (std::ifstream::failure e)
				{
					AE_CORE_ERROR("Geometry Shader File failed to read!: {0}", e.what());
				}
			}
		}
	}
	void Shader::CheckComplied(unsigned shader, std::string type)
	{
		GLint Completed;
		GLchar infoLog[1024];

		if(type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &Completed);
			if(!Completed)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				AE_CORE_ERROR("Shader failed to COMPILE of Type:{0} \n LOG:{1}", type, infoLog );
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &Completed);
			if(!Completed)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				AE_CORE_ERROR("Shader failed to LINK of Type:{0} \n LOG:{1}", type, infoLog );
			}
		}
	}
	
	void Shader::GenerateTextures()
	{
		{
			//Generates and binds 1st texture
			std::string AppPath = __argv[0];	
			AppPath.replace(AppPath.end() - 11, AppPath.end(), "Textures\\container2.png");
			const char* tPath = AppPath.c_str();

			glGenTextures(1, &texture0);
			glBindTexture(GL_TEXTURE_2D, texture0);

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			int width, height, nrchannels;
			stbi_set_flip_vertically_on_load(true); 
			unsigned char *data = stbi_load(tPath, &width, &height, &nrchannels, 0);

			if(data)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				AE_CORE_ERROR("Texture failed to load!");
			}	
			stbi_image_free(data);
		}

		{
			//Generates and binds 2nd texture
			std::string AppPath = __argv[0];	
			AppPath.replace(AppPath.end() - 11, AppPath.end(), "Textures\\container2_specular.png");
			const char* tPath = AppPath.c_str();

			glGenTextures(1, &texture1);
			glBindTexture(GL_TEXTURE_2D, texture1);

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			int width, height, nrchannels;
			stbi_set_flip_vertically_on_load(true); 
			unsigned char *data = stbi_load(tPath, &width, &height, &nrchannels, 0);

			if(data)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				AE_CORE_ERROR("Texture failed to load!");
			}	
			stbi_image_free(data);
		}
		//TODO: Setup the ability for multiple textures to be used in one shader
	}
	void Shader::BindTextures(unsigned int id)
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}
	void Shader::SetActiveTexture(int num)
	{
		glActiveTexture(GL_TEXTURE0 + num);
	}
	
	void Shader::SetUniformMatrix4(const std::string& name, const glm::mat4& matrix)
	{	
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1,	GL_FALSE ,glm::value_ptr(matrix));
	}
	void Shader::SetUniformBool(const std::string& name, bool value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}
	void Shader::SetUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}
	void Shader::SetUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}
	void Shader::SetUniformVec3(const std::string& name, glm::vec3 value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.r, value.g, value.b);
	}

}
