#define UNICITY_DEBUG

#define UE_NO_CURSOR NULL

#define UNICITY_USE_NATIVE_WINDOW

#define UNICITY_PLATFORM_WIN32

#define WINDOWS_TIMER				0

#define GAU_THREAD_POLICY_MULTI		2

#define UNICITY_VERTEX_ARRAYS		1

#define SHADER_VERTEX_INDEX			0
#define SHADER_UV_INDEX				1
#define SHADER_MASK_UV_INDEX		2
#define SHADER_TID_INDEX			3
#define SHADER_MID_INDEX			4
#define SHADER_COLOR_INDEX			5

#define RENDERER_MAX_SPRITES		60000
#define RENDERER_VERTEX_SIZE		sizeof(VertexData)
#define RENDERER_SPRITE_SIZE		RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE		RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE		RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES		32 - 1

//Native Window defines

#ifdef UNICITY_USE_NATIVE_WINDOW

#define SP_MOUSE_LEFT	  0x00
#define SP_MOUSE_MIDDLE	  0x01
#define SP_MOUSE_RIGHT    0x02

#define VK_0			  0x30
#define VK_1			  0x31
#define VK_2			  0x32
#define VK_3			  0x33
#define VK_4			  0x34
#define VK_5			  0x35
#define VK_6			  0x36
#define VK_7			  0x37
#define VK_8			  0x38
#define VK_9			  0x39

#define VK_A			  0x41
#define VK_B			  0x42
#define VK_C			  0x43
#define VK_D			  0x44
#define VK_E			  0x45
#define VK_F			  0x46
#define VK_G			  0x47
#define VK_H			  0x48
#define VK_I			  0x49
#define VK_J			  0x4A
#define VK_K			  0x4B
#define VK_L			  0x4C
#define VK_M			  0x4D
#define VK_N			  0x4E
#define VK_O			  0x4F
#define VK_P			  0x50
#define VK_Q			  0x51
#define VK_R			  0x52
#define VK_S			  0x53
#define VK_T			  0x54
#define VK_U			  0x55
#define VK_V			  0x56
#define VK_W			  0x57
#define VK_X			  0x58
#define VK_Y			  0x59
#define VK_Z			  0x5A

#define VK_LBUTTON        0x01
#define VK_RBUTTON        0x02
#define VK_CANCEL         0x03
#define VK_MBUTTON        0x04

#define VK_ESCAPE         0x1B
#define VK_SHIFT          0x10
#define VK_CONTROL        0x11
#define VK_MENU           0x12
#define VK_PAUSE          0x13
#define VK_CAPITAL        0x14

#define VK_SPACE          0x20
#define VK_PRIOR          0x21
#define VK_NEXT           0x22
#define VK_END            0x23
#define VK_HOME           0x24
#define VK_LEFT           0x25
#define VK_UP             0x26
#define VK_RIGHT          0x27
#define VK_DOWN           0x28
#define VK_SELECT         0x29
#define VK_PRINT          0x2A
#define VK_EXECUTE        0x2B
#define VK_SNAPSHOT       0x2C
#define VK_INSERT         0x2D
#define VK_DELETE         0x2E
#define VK_HELP           0x2F

#define VK_NUMPAD0        0x60
#define VK_NUMPAD1        0x61
#define VK_NUMPAD2        0x62
#define VK_NUMPAD3        0x63
#define VK_NUMPAD4        0x64
#define VK_NUMPAD5        0x65
#define VK_NUMPAD6        0x66
#define VK_NUMPAD7        0x67
#define VK_NUMPAD8        0x68
#define VK_NUMPAD9        0x69
#define VK_MULTIPLY       0x6A
#define VK_ADD            0x6B
#define VK_SEPARATOR      0x6C
#define VK_SUBTRACT       0x6D
#define VK_DECIMAL        0x6E
#define VK_DIVIDE         0x6F
#define VK_F1             0x70
#define VK_F2             0x71
#define VK_F3             0x72
#define VK_F4             0x73
#define VK_F5             0x74
#define VK_F6             0x75
#define VK_F7             0x76
#define VK_F8             0x77
#define VK_F9             0x78
#define VK_F10            0x79
#define VK_F11            0x7A
#define VK_F12            0x7B
#define VK_F13            0x7C
#define VK_F14            0x7D
#define VK_F15            0x7E
#define VK_F16            0x7F
#define VK_F17            0x80
#define VK_F18            0x81
#define VK_F19            0x82
#define VK_F20            0x83
#define VK_F21            0x84
#define VK_F22            0x85
#define VK_F23            0x86
#define VK_F24            0x87

#define VK_NUMLOCK        0x90
#define VK_SCROLL         0x91

#define VK_LSHIFT         0xA0
#define VK_RSHIFT         0xA1
#define VK_LCONTROL       0xA2
#define VK_RCONTROL       0xA3
#define VK_LMENU          0xA4
#define VK_RMENU          0xA5

#endif