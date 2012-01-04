#ifndef NXLIB_FORWARDDECL_H_
#define NXLIB_FORWARDDECL_H_

// nx::animation
namespace nx {namespace animation {
class AnimationHelper;
class AnimationManagerEventHandler;
class IAnimationStatusChangedListener;
}}

// nx::core
namespace nx {namespace core {
class GLContext;
class NXApplication;
}}

// nx::event
namespace nx {namespace event {
class IGLRenderEventListener;
}}

// nx::math
namespace nx {namespace math {
class Float;
}}

// nx::mui
namespace nx {namespace mui {
class MUI;
}}

// nx::ribbon
namespace nx {namespace ribbon {
class IRibbonCommandListener;
class RibbonCommandHandler;
class RibbonFramework;
}}

// nx::touch
namespace nx {namespace touch {
class AbstractManipulationHelper;
class IManipulationEventListener;
class ManipulationHelper;
class ManipulationResult;
}}

// nx::tsf
namespace nx {namespace tsf {
class Message;
class MessageQueue;
class TSFManager;
}}

// nx::util
namespace nx {namespace util {
class FeatureLevel;
class OSVersionChecker;
class StringUtil;
class WMessageArgs;
class LastErrorArgs;
}}

// nx::win
namespace nx {namespace win {
class CanvasWindow;
class MainWindow;
}}

#endif // NXLIB_FORWARDDECL_H_
