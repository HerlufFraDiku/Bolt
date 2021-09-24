#pragma once

namespace Bolt {
	enum class ShaderElementType : uint32_t {
		None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Bool
	};

	static int32_t ShaderElementTypeSize(ShaderElementType type) {
		switch (type)
		{
			case Bolt::ShaderElementType::None:   return 0;
			case Bolt::ShaderElementType::Float:  return 4;
			case Bolt::ShaderElementType::Float2: return 4 * 2;
			case Bolt::ShaderElementType::Float3: return 4 * 3;
			case Bolt::ShaderElementType::Float4: return 4 * 4;
			case Bolt::ShaderElementType::Int:    return 4;
			case Bolt::ShaderElementType::Int2:   return 4 * 2;
			case Bolt::ShaderElementType::Int3:   return 4 * 3;
			case Bolt::ShaderElementType::Int4:   return 4 * 4;
			case Bolt::ShaderElementType::Mat3:   return 4 * 3 * 3;
			case Bolt::ShaderElementType::Mat4:   return 4 * 4 * 4;
			case Bolt::ShaderElementType::Bool:   return 1;

			default: {
				BL_CORE_ASSERT("Unknown ShaderElementType!");
				return 0;
			}
		}
	}

	struct BufferElement {
		std::string Name;
		ShaderElementType Type;
		bool Normalized;
		int32_t Size;
		int32_t Offset;

		BufferElement(): Name("BufferElement"), Type(Bolt::ShaderElementType::None), Normalized(false), Size(0), Offset(0) {}
		BufferElement(ShaderElementType type, const std::string name, bool normalized = false) : Name(name), Type(type), Size(ShaderElementTypeSize(type)), Offset(0), Normalized(normalized) {}

		uint32_t GetComponentCount() {
			switch (Type)
			{
				case Bolt::ShaderElementType::None:   return 0;
				case Bolt::ShaderElementType::Float:  return 1;
				case Bolt::ShaderElementType::Float2: return 2;
				case Bolt::ShaderElementType::Float3: return 3;
				case Bolt::ShaderElementType::Float4: return 4;
				case Bolt::ShaderElementType::Int:    return 1;
				case Bolt::ShaderElementType::Int2:	  return 2;
				case Bolt::ShaderElementType::Int3:   return 3;
				case Bolt::ShaderElementType::Int4:   return 4;
				case Bolt::ShaderElementType::Mat3:   return 3 * 3;
				case Bolt::ShaderElementType::Mat4:   return 4 * 4;
				case Bolt::ShaderElementType::Bool:   return 1;

				default: {
					BL_CORE_ASSERT("Unknown ShaderElementType!");
					return 0;
				}
			}
		}
	};

	class BufferLayout {
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {
			CalculateOffsetAndStride();
		}
	
		inline uint32_t GetStride() { return m_Stride; }

		inline const std::vector<BufferElement>& GetElements() { return m_Elements; }
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetAndStride() {
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {};

		virtual void Load(uint32_t size, void* verticies) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static Ref<VertexBuffer> Create(uint32_t size, float* vertices = nullptr);
		static Ref<VertexBuffer> CreateDynamic(uint32_t size, float* vertices = nullptr);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {};

		virtual void Load(uint32_t size, void* indicies) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint32_t GetCount() = 0;

		static Ref<IndexBuffer> Create(uint32_t size, uint32_t* indicies = nullptr);
		static Ref<IndexBuffer> CreateDynamic(uint32_t size, uint32_t* indicies = nullptr);
	};

}