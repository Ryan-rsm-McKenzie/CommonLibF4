#pragma once

#include "RE/Bethesda/BSStringT.h"
#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/BSTSingleton.h"
#include "RE/Scaleform/GFx/GFx_Player.h"
#include "RE/Scaleform/Kernel/SF_RefCount.h"

namespace RE
{
	class BSScaleformImageLoader;
	class IMenu;

	namespace Scaleform
	{
		namespace GFx
		{
			class DrawTextManager;
			class Loader;
		}

		namespace Render
		{
			class HAL;
			class Renderer2D;
			class RenderTarget;
			class TextureManager;
		}
	}

	struct SFRendererInitializedEvent
	{
	public:
	};
	static_assert(std::is_empty_v<SFRendererInitializedEvent>);

	struct BSScaleformRenderer :
		public BSTEventSource<SFRendererInitializedEvent>  // 000
	{
	public:
		void Initialize()
		{
			using func_t = decltype(&BSScaleformRenderer::Initialize);
			REL::Relocation<func_t> func{ REL::ID(1403529) };
			return func(this);
		}

		// members
		Scaleform::Ptr<Scaleform::Render::Renderer2D> renderer;            // 058
		Scaleform::Ptr<Scaleform::Render::HAL> renderConfig;               // 060
		Scaleform::Ptr<Scaleform::Render::TextureManager> textureManager;  // 068
		Scaleform::Render::RenderTarget* renderTargets[100];               // 070
		bool initialized;                                                  // 390
	};
	static_assert(sizeof(BSScaleformRenderer) == 0x398);

	class __declspec(novtable) BSScaleformManager :
		public BSTEventSink<SFRendererInitializedEvent>,  // 00
		public BSTSingletonSDM<BSScaleformManager>        // 08
	{
	public:
		static constexpr auto RTTI{ RTTI::BSScaleformManager };
		static constexpr auto VTABLE{ VTABLE::BSScaleformManager };

		using ScaleModeType = Scaleform::GFx::Movie::ScaleModeType;

		[[nodiscard]] static BSScaleformManager* GetSingleton()
		{
			REL::Relocation<BSScaleformManager**> singleton{ REL::ID(106578) };
			return *singleton;
		}

		bool LoadMovie(
			IMenu& a_menu,
			Scaleform::Ptr<Scaleform::GFx::Movie>& a_movie,
			const char* a_menuName,
			const char* a_menuObjPath = nullptr,
			ScaleModeType a_scaleMode = ScaleModeType::kShowAll,
			float a_backgroundAlpha = 0.0F)
		{
			using func_t = decltype(&BSScaleformManager::LoadMovie);
			REL::Relocation<func_t> func{ REL::ID(1526234) };
			return func(this, a_menu, a_movie, a_menuName, a_menuObjPath, a_scaleMode, a_backgroundAlpha);
		}

		bool LoadMovieEx(
			IMenu& a_menu,
			stl::zstring a_filePath,
			stl::zstring a_menuObjPath = ""sv,
			ScaleModeType a_scaleMode = ScaleModeType::kShowAll,
			float a_backgroundAlpha = 0.0F);

		// members
		Scaleform::GFx::Loader* loader;                               // 10
		BSScaleformRenderer* renderer;                                // 18
		Scaleform::Ptr<Scaleform::GFx::DrawTextManager> textManager;  // 20
		Scaleform::Ptr<BSScaleformImageLoader> imageLoader;           // 28
		BSStringT<char> validNameChars;                               // 30

	private:
		[[nodiscard]] bool GetMovieFilename(char const* a_menuName, BSStaticStringT<260>& a_filePath)
		{
			using func_t = decltype(&BSScaleformManager::GetMovieFilename);
			REL::Relocation<func_t> func{ REL::ID(1191277) };
			return func(this, a_menuName, a_filePath);
		}

		void InitMovieViewport(Scaleform::GFx::Movie& a_movie, const float a_dynamicWidthRatio, const float a_dynamicHeightRatio)
		{
			using func_t = decltype(&BSScaleformManager::InitMovieViewport);
			REL::Relocation<func_t> func{ REL::ID(206895) };
			return func(this, a_movie, a_dynamicWidthRatio, a_dynamicHeightRatio);
		}
	};
	static_assert(sizeof(BSScaleformManager) == 0x40);
}
