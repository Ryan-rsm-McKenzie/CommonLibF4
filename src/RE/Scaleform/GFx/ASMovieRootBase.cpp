#include "RE/Scaleform/GFx/ASMovieRootBase.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			ASMovieRootBase::ASMovieRootBase(ASSupport* a_asSupport) :
				_movieImpl(0),
				_asSupport(a_asSupport),
				_avmVersion(a_asSupport->GetAVMVersion())
			{}


			void ASMovieRootBase::SetMovie(MovieImpl* a_movie)
			{
				_movieImpl = a_movie;
			}


			void ASMovieRootBase::GenerateTouchEvents(UInt32 a_mouseStateIndex)
			{
				return;
			}


			void ASMovieRootBase::GenerateGestureEvents(InteractiveObject* a_topmost, UInt32 a_phase, const Render::PointF& a_pos, const Render::PointF& a_offset, const Render::PointF& a_scale, float a_rotation, UInt32 a_gestureMask)
			{
				return;
			}


			void ASMovieRootBase::OnDeviceOrientationChanged(const OrientationEvent& a_event)
			{
				return;
			}


			void ASMovieRootBase::OnAppLifecycleEvent(const AppLifecycleEvent& a_event)
			{
				return;
			}


			void ASMovieRootBase::PrintObjectsReport(UInt32 a_flags, Log* a_log, const char* a_swfName)
			{
				return;
			}


			void ASMovieRootBase::ProcessLoadBinaryMT(LoadQueueEntry* a_entry, LoadStates* a_ls, const ArrayPOD<UInt8>& a_data, UPInt a_fileLen, bool a_succeeded)
			{
				return;
			}


			SInt32 ASMovieRootBase::GetAVMVersion() const
			{
				return _avmVersion;
			}


			ASSupport* ASMovieRootBase::GetASSupport() const
			{
				return _asSupport.get();
			}


			MovieImpl* ASMovieRootBase::GetMovieImpl() const
			{
				return _movieImpl;
			}
		}
	}
}
