#include "blpch.h"
#include "Bolt/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Bolt {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}