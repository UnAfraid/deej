package wca

import (
	"github.com/go-ole/go-ole"
)

type PROPERTYKEY struct {
	ole.GUID
	PID uint32
}

var (
	PKEY_DeviceInterface_FriendlyName            = DefinePropertyKey(0x026e516e, 0xb814, 0x414b, 0x83, 0xcd, 0x85, 0x6d, 0x6f, 0xef, 0x48, 0x22, 2)
	PKEY_Device_DeviceDesc                       = DefinePropertyKey(0xa45c254e, 0xdf1c, 0x4efd, 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0, 2)
	PKEY_Device_FriendlyName                     = DefinePropertyKey(0xa45c254e, 0xdf1c, 0x4efd, 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0, 14)
	PKEY_AudioEndpoint_FormFactor                = DefinePropertyKey(0x1da5d803, 0xd492, 0x4edd, 0x8c, 0x23, 0xe0, 0xc0, 0xff, 0xee, 0x7f, 0x0e, 0)
	PKEY_AudioEndpoint_ControlPanelPageProvider  = DefinePropertyKey(0x1da5d803, 0xd492, 0x4edd, 0x8c, 0x23, 0xe0, 0xc0, 0xff, 0xee, 0x7f, 0x0e, 1)
	PKEY_AudioEndpoint_Association               = DefinePropertyKey(0x1da5d803, 0xd492, 0x4edd, 0x8c, 0x23, 0xe0, 0xc0, 0xff, 0xee, 0x7f, 0x0e, 2)
	PKEY_AudioEndpoint_PhysicalSpeakers          = DefinePropertyKey(0x1da5d803, 0xd492, 0x4edd, 0x8c, 0x23, 0xe0, 0xc0, 0xff, 0xee, 0x7f, 0x0e, 3)
	PKEY_AudioEndpoint_GUID                      = DefinePropertyKey(0x1da5d803, 0xd492, 0x4edd, 0x8c, 0x23, 0xe0, 0xc0, 0xff, 0xee, 0x7f, 0x0e, 4)
	PKEY_AudioEndpoint_Disable_SysFx             = DefinePropertyKey(0x1da5d803, 0xd492, 0x4edd, 0x8c, 0x23, 0xe0, 0xc0, 0xff, 0xee, 0x7f, 0x0e, 5)
	PKEY_AudioEndpoint_FullRangeSpeakers         = DefinePropertyKey(0x1da5d803, 0xd492, 0x4edd, 0x8c, 0x23, 0xe0, 0xc0, 0xff, 0xee, 0x7f, 0x0e, 6)
	PKEY_AudioEndpoint_Supports_EventDriven_Mode = DefinePropertyKey(0x1da5d803, 0xd492, 0x4edd, 0x8c, 0x23, 0xe0, 0xc0, 0xff, 0xee, 0x7f, 0x0e, 7)
	PKEY_AudioEndpoint_JackSubType               = DefinePropertyKey(0x1da5d803, 0xd492, 0x4edd, 0x8c, 0x23, 0xe0, 0xc0, 0xff, 0xee, 0x7f, 0x0e, 8)
	PKEY_AudioEngine_DeviceFormat                = DefinePropertyKey(0xf19f064d, 0x82c, 0x4e27, 0xbc, 0x73, 0x68, 0x82, 0xa1, 0xbb, 0x8e, 0x4c, 0)
	PKEY_AudioEngine_OEMFormat                   = DefinePropertyKey(0xe4870e26, 0x3cc5, 0x4cd2, 0xba, 0x46, 0xca, 0xa, 0x9a, 0x70, 0xed, 0x4, 3)
)

func DefinePropertyKey(l uint32, w1, w2 uint16, b1, b2, b3, b4, b5, b6, b7, b8 byte, pid uint32) PROPERTYKEY {
	g := ole.GUID{
		Data1: l,
		Data2: w1,
		Data3: w2,
		Data4: [8]byte{b1, b2, b3, b4, b5, b6, b7, b8},
	}
	return PROPERTYKEY{g, pid}
}
