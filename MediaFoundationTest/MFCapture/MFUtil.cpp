#include "stdafx.h"
#include "MFUtil.h"
//#define SHOWMESSAGEBOX
namespace MFCapture
{
	void MFUtil::ShowErrorNameFromCode(HRESULT code)
	{
		System::String^ str = nullptr;
		int tableSize = (sizeof(MFUtil::MFErrorTable) / sizeof(MFUtil::MFErrorTable[0]));

		for (int i = 0; i < tableSize; i++)
		{
			if (code == MFUtil::MFErrorTable[i].Code)
			{
				str = gcnew System::String(MFUtil::MFErrorTable[i].Name);
#ifdef SHOWMESSAGEBOX
				MessageBox(NULL, MFUtil::MFErrorTable[i].Name, TEXT("Error"), MB_OK);
#endif
				System::Diagnostics::Debug::WriteLine(System::String::Concat("Error       : ", str));
				return;
			}
		}

#ifdef SHOWMESSAGEBOX
		MessageBox(NULL, TEXT("Unknown Error."), TEXT("Error"), MB_OK);
#endif
		System::Diagnostics::Debug::WriteLine("Error       : Unknown Error.");
	}

	void MFUtil::ShowErrorDescriptionFromCode(HRESULT code)
	{
		System::String^ str = nullptr;
		int tableSize = (sizeof(MFUtil::MFErrorTable) / sizeof(MFUtil::MFErrorTable[0]));

		for (int i = 0; i < tableSize; i++)
		{
			if (code == MFUtil::MFErrorTable[i].Code)
			{
				str = gcnew System::String(MFUtil::MFErrorTable[i].Description);
#ifdef SHOWMESSAGEBOX
				MessageBox(NULL, MFUtil::MFErrorTable[i].Description, TEXT("Error"), MB_OK);
#endif
				System::Diagnostics::Debug::WriteLine(System::String::Concat("Error       : ", str));
				return;
			}
		}

#ifdef SHOWMESSAGEBOX
		MessageBox(NULL, TEXT("Unknown Error."), TEXT("Error"), MB_OK);
#endif
		System::Diagnostics::Debug::WriteLine("Error       : Unknown Error.");
		/*
		LPTSTR name = NULL;
		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			code,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &name,
			0,
			NULL
		);
		MessageBox(NULL, name, TEXT("Error"), MB_OK);
		*/
	}

	void MFUtil::ShowMessage(LPCTSTR message, MessageLevel ml)
	{
		System::String^ str = gcnew System::String(message);

		switch (ml)
		{
		case MFCapture::ML_DEBUG:
#ifdef _DEBUG
#ifdef SHOWMESSAGEBOX
			MessageBox(NULL, message, TEXT("Debug"), MB_OK);
#endif
			System::Diagnostics::Debug::WriteLine(System::String::Concat("Info(Debug) : ", str));
#endif
			break;
		case MFCapture::ML_INFO:
#ifdef SHOWMESSAGEBOX
			MessageBox(NULL, message, TEXT("Info"), MB_OK);
#endif
			System::Diagnostics::Debug::WriteLine(System::String::Concat("Info        : ", str));
			break;
		case MFCapture::ML_WARN:
#ifdef SHOWMESSAGEBOX
			MessageBox(NULL, message, TEXT("Warning"), MB_OK);
#endif
			System::Diagnostics::Debug::WriteLine(System::String::Concat("Warning     : ", str));
			break;
		case MFCapture::ML_ERROR:
#ifdef SHOWMESSAGEBOX
			MessageBox(NULL, message, TEXT("Error"), MB_OK);
#endif
			System::Diagnostics::Debug::WriteLine(System::String::Concat("Error       : ", str));
			break;
		default:
			break;
		}
	}

	const ErrorTable MFUtil::MFErrorTable[] = {
		{0x00000000 , _T("Operation successful"), _T("S_OK")},
		{0x80004001 , _T("Not implemented"), _T("E_NOTIMPL")},
		{0x80004002 , _T("No such interface supported"), _T("E_NOINTERFACE")},
		{0x80004003 , _T("Pointer that is not valid"), _T("E_POINTER")},
		{0x80004004 , _T("Operation aborted"), _T("E_ABORT")},
		{0x80004005 , _T("Unspecified failure"), _T("E_FAIL")},
		{0x8000FFFF , _T("Unexpected failure"), _T("E_UNEXPECTED")},
		{0x80070005 , _T("General access denied error"), _T("E_ACCESSDENIED")},
		{0x80070006 , _T("Handle that is not valid"), _T("E_HANDLE")},
		{0x8007000E , _T("Failed to allocate necessary memory"), _T("E_OUTOFMEMORY")},
		{0x80070057 , _T("One or more arguments are not valid"), _T("E_INVALIDARG")},
		{0xC00D36B0 , _T("Platform not initialized. Please call MFStartup()."), _T("MF_E_PLATFORM_NOT_INITIALIZED")},
		{0xC00D36B1 , _T("The buffer was too small to carry out the requested action."), _T("MF_E_BUFFERTOOSMALL")},
		{0xC00D36B2 , _T("The request is invalid in the current state."), _T("MF_E_INVALIDREQUEST")},
		{0xC00D36B3 , _T("The stream number provided was invalid."), _T("MF_E_INVALIDSTREAMNUMBER")},
		{0xC00D36B4 , _T("The data specified for the media type is invalid, inconsistent, or not supported by this object."), _T("MF_E_INVALIDMEDIATYPE")},
		{0xC00D36B5 , _T("The callee is currently not accepting further input."), _T("MF_E_NOTACCEPTING")},
		{0xC00D36B6 , _T("This object needs to be initialized before the requested operation can be carried out."), _T("MF_E_NOT_INITIALIZED")},
		{0xC00D36B7 , _T("The requested representation is not supported by this object."), _T("MF_E_UNSUPPORTED_REPRESENTATION")},
		{0xC00D36B9 , _T("An object ran out of media types to suggest therefore the requested chain of streaming objects cannot be completed."), _T("MF_E_NO_MORE_TYPES")},
		{0xC00D36BA , _T("The object does not support the specified service."), _T("MF_E_UNSUPPORTED_SERVICE")},
		{0xC00D36BB , _T("An unexpected error has occurred in the operation requested."), _T("MF_E_UNEXPECTED")},
		{0xC00D36BC , _T("Invalid name."), _T("MF_E_INVALIDNAME")},
		{0xC00D36BD , _T("Invalid type."), _T("MF_E_INVALIDTYPE")},
		{0xC00D36BE , _T("The file does not conform to the relevant file format specification."), _T("MF_E_INVALID_FILE_FORMAT")},
		{0xC00D36BF , _T("Invalid index."), _T("MF_E_INVALIDINDEX")},
		{0xC00D36C0 , _T("An invalid timestamp was given."), _T("MF_E_INVALID_TIMESTAMP")},
		{0xC00D36C3 , _T("The scheme of the given URL is unsupported."), _T("MF_E_UNSUPPORTED_SCHEME")},
		{0xC00D36C4 , _T("The byte stream type of the given URL is unsupported."), _T("MF_E_UNSUPPORTED_BYTESTREAM_TYPE")},
		{0xC00D36C5 , _T("The given time format is unsupported."), _T("MF_E_UNSUPPORTED_TIME_FORMAT")},
		{0xC00D36C8 , _T("The Media Sample does not have a timestamp."), _T("MF_E_NO_SAMPLE_TIMESTAMP")},
		{0xC00D36C9 , _T("The Media Sample does not have a duration."), _T("MF_E_NO_SAMPLE_DURATION")},
		{0xC00D36CB , _T("The request failed because the data in the stream is corrupt.%0\n."), _T("MF_E_INVALID_STREAM_DATA")},
		{0xC00D36CF , _T("Real time services are not available."), _T("MF_E_RT_UNAVAILABLE")},
		{0xC00D36D0 , _T("The specified rate is not supported."), _T("MF_E_UNSUPPORTED_RATE")},
		{0xC00D36D1 , _T("This component does not support stream-thinning."), _T("MF_E_THINNING_UNSUPPORTED")},
		{0xC00D36D2 , _T("The call failed because no reverse playback rates are available."), _T("MF_E_REVERSE_UNSUPPORTED")},
		{0xC00D36D3 , _T("The requested rate transition cannot occur in the current state."), _T("MF_E_UNSUPPORTED_RATE_TRANSITION")},
		{0xC00D36D4 , _T("The requested rate change has been pre-empted and will not occur."), _T("MF_E_RATE_CHANGE_PREEMPTED")},
		{0xC00D36D5 , _T("The specified object or value does not exist."), _T("MF_E_NOT_FOUND")},
		{0xC00D36D6 , _T("The requested value is not available."), _T("MF_E_NOT_AVAILABLE")},
		{0xC00D36D7 , _T("The specified operation requires a clock and no clock is available."), _T("MF_E_NO_CLOCK")},
		{0x000D36D8 , _T("This callback and state had already been passed in to this event generator earlier."), _T("MF_S_MULTIPLE_BEGIN")},
		{0xC00D36D9 , _T("This callback has already been passed in to this event generator."), _T("MF_E_MULTIPLE_BEGIN")},
		{0xC00D36DA , _T("Some component is already listening to events on this event generator."), _T("MF_E_MULTIPLE_SUBSCRIBERS")},
		{0xC00D36DB , _T("This timer was orphaned before its callback time arrived."), _T("MF_E_TIMER_ORPHANED")},
		{0xC00D36DC , _T("A state transition is already pending."), _T("MF_E_STATE_TRANSITION_PENDING")},
		{0xC00D36DD , _T("The requested state transition is unsupported."), _T("MF_E_UNSUPPORTED_STATE_TRANSITION")},
		{0xC00D36DE , _T("An unrecoverable error has occurred."), _T("MF_E_UNRECOVERABLE_ERROR_OCCURRED")},
		{0xC00D36DF , _T("The provided sample has too many buffers."), _T("MF_E_SAMPLE_HAS_TOO_MANY_BUFFERS")},
		{0xC00D36E0 , _T("The provided sample is not writable."), _T("MF_E_SAMPLE_NOT_WRITABLE")},
		{0xC00D36E2 , _T("The specified key is not valid."), _T("MF_E_INVALID_KEY")},
		{0xC00D36E3 , _T("You are calling MFStartup with the wrong MF_VERSION. Mismatched bits?"), _T("MF_E_BAD_STARTUP_VERSION")},
		{0xC00D36E4 , _T("The caption of the given URL is unsupported."), _T("MF_E_UNSUPPORTED_CAPTION")},
		{0xC00D36E5 , _T("The operation on the current offset is not permitted."), _T("MF_E_INVALID_POSITION")},
		{0xC00D36E6 , _T("The requested attribute was not found."), _T("MF_E_ATTRIBUTENOTFOUND")},
		{0xC00D36E7 , _T("The specified property type is not allowed in this context."), _T("MF_E_PROPERTY_TYPE_NOT_ALLOWED")},
		{0xC00D36E8 , _T("The specified property type is not supported."), _T("MF_E_PROPERTY_TYPE_NOT_SUPPORTED")},
		{0xC00D36E9 , _T("The specified property is empty."), _T("MF_E_PROPERTY_EMPTY")},
		{0xC00D36EA , _T("The specified property is not empty."), _T("MF_E_PROPERTY_NOT_EMPTY")},
		{0xC00D36EB , _T("The vector property specified is not allowed in this context."), _T("MF_E_PROPERTY_VECTOR_NOT_ALLOWED")},
		{0xC00D36EC , _T("A vector property is required in this context."), _T("MF_E_PROPERTY_VECTOR_REQUIRED")},
		{0xC00D36ED , _T("The operation is cancelled."), _T("MF_E_OPERATION_CANCELLED")},
		{0xC00D36EE , _T("The provided bytestream was expected to be seekable and it is not."), _T("MF_E_BYTESTREAM_NOT_SEEKABLE")},
		{0xC00D36EF , _T("The Media Foundation platform is disabled when the system is running in Safe Mode."), _T("MF_E_DISABLED_IN_SAFEMODE")},
		{0xC00D36F0 , _T("The Media Source could not parse the byte stream."), _T("MF_E_CANNOT_PARSE_BYTESTREAM")},
		{0xC00D36F1 , _T("Mutually exclusive flags have been specified to source resolver. This flag combination is invalid."), _T("MF_E_SOURCERESOLVER_MUTUALLY_EXCLUSIVE_FLAGS")},
		{0xC00D36F2 , _T("MediaProc is in the wrong state"), _T("MF_E_MEDIAPROC_WRONGSTATE")},
		{0xC00D36F3 , _T("Real time I/O service can not provide requested throughput."), _T("MF_E_RT_THROUGHPUT_NOT_AVAILABLE")},
		{0xC00D36F4 , _T("The workqueue cannot be registered with more classes."), _T("MF_E_RT_TOO_MANY_CLASSES")},
		{0xC00D36F5 , _T("This operation cannot succeed because another thread owns this object."), _T("MF_E_RT_WOULDBLOCK")},
		{0xC00D36F6 , _T("Internal. Bitpump not found."), _T("MF_E_NO_BITPUMP")},
		{0xC00D36F7 , _T("No more RT memory available."), _T("MF_E_RT_OUTOFMEMORY")},
		{0xC00D36F8 , _T("An MMCSS class has not been set for this work queue."), _T("MF_E_RT_WORKQUEUE_CLASS_NOT_SPECIFIED")},
		{0xC00D36FA , _T("Activate failed to create mediasink. Call OutputNode::GetUINT32(MF_TOPONODE_MAJORTYPE) for more information. "), _T("MF_E_CANNOT_CREATE_SINK")},
		{0xC00D36FB , _T("The length of the provided bytestream is unknown."), _T("MF_E_BYTESTREAM_UNKNOWN_LENGTH")},
		{0xC00D36FC , _T("The media session cannot pause from a stopped state."), _T("MF_E_SESSION_PAUSEWHILESTOPPED")},
		{0x000D36FD , _T("The activate could not be created in the remote process for some reason it was replaced with empty one."), _T("MF_S_ACTIVATE_REPLACED")},
		{0xC00D36FE , _T("The data specified for the media type is supported, but would require a format change, which is not supported by this object."), _T("MF_E_FORMAT_CHANGE_NOT_SUPPORTED")},
		{0xC00D3A98 , _T("Not enough data have been parsed to carry out the requested action."), _T("MF_E_ASF_PARSINGINCOMPLETE")},
		{0x400D3A98 , _T("Parsing is still in progress and is not yet complete."), _T("MF_S_ASF_PARSEINPROGRESS")},
		{0xC00D3A99 , _T("There is a gap in the ASF data provided."), _T("MF_E_ASF_MISSINGDATA")},
		{0xC00D3A9A , _T("The data provided are not valid ASF."), _T("MF_E_ASF_INVALIDDATA")},
		{0xC00D3A9B , _T("The packet is opaque, so the requested information cannot be returned."), _T("MF_E_ASF_OPAQUEPACKET")},
		{0xC00D3A9C , _T("The requested operation failed since there is no appropriate ASF index."), _T("MF_E_ASF_NOINDEX")},
		{0xC00D3A9D , _T("The value supplied is out of range for this operation."), _T("MF_E_ASF_OUTOFRANGE")},
		{0xC00D3A9E , _T("The index entry requested needs to be loaded before it can be available."), _T("MF_E_ASF_INDEXNOTLOADED")},
		{0xC00D3A9F , _T("The packet has reached the maximum number of payloads."), _T("MF_E_ASF_TOO_MANY_PAYLOADS")},
		{0xC00D3AA0 , _T("Stream type is not supported."), _T("MF_E_ASF_UNSUPPORTED_STREAM_TYPE")},
		{0xC00D3E80 , _T("There are no events available in the queue."), _T("MF_E_NO_EVENTS_AVAILABLE")},
		{0xC00D3E82 , _T("A media source cannot go from the stopped state to the paused state."), _T("MF_E_INVALID_STATE_TRANSITION")},
		{0xC00D3E84 , _T("The media stream cannot process any more samples because there are no more samples in the stream."), _T("MF_E_END_OF_STREAM")},
		{0xC00D3E85 , _T("The request is invalid because Shutdown() has been called."), _T("MF_E_SHUTDOWN")},
		{0xC00D3E86 , _T("The MP3 object was not found."), _T("MF_E_MP3_NOTFOUND")},
		{0xC00D3E87 , _T("The MP3 parser ran out of data before finding the MP3 object."), _T("MF_E_MP3_OUTOFDATA")},
		{0xC00D3E88 , _T("The file is not really a MP3 file."), _T("MF_E_MP3_NOTMP3")},
		{0xC00D3E89 , _T("The MP3 file is not supported."), _T("MF_E_MP3_NOTSUPPORTED")},
		{0xC00D3E8A , _T("The Media stream has no duration."), _T("MF_E_NO_DURATION")},
		{0xC00D3E8C , _T("The Media format is recognized but is invalid."), _T("MF_E_INVALID_FORMAT")},
		{0xC00D3E8D , _T("The property requested was not found."), _T("MF_E_PROPERTY_NOT_FOUND")},
		{0xC00D3E8E , _T("The property is read only."), _T("MF_E_PROPERTY_READ_ONLY")},
		{0xC00D3E8F , _T("The specified property is not allowed in this context."), _T("MF_E_PROPERTY_NOT_ALLOWED")},
		{0xC00D3E91 , _T("The media source is not started."), _T("MF_E_MEDIA_SOURCE_NOT_STARTED")},
		{0xC00D3E98 , _T("The Media format is recognized but not supported."), _T("MF_E_UNSUPPORTED_FORMAT")},
		{0xC00D3E99 , _T("The MPEG frame has bad CRC."), _T("MF_E_MP3_BAD_CRC")},
		{0xC00D3E9A , _T("The file is not protected."), _T("MF_E_NOT_PROTECTED")},
		{0xC00D3E9B , _T("The media source is in the wrong state"), _T("MF_E_MEDIA_SOURCE_WRONGSTATE")},
		{0xC00D4268 , _T("An attempt to acquire a network resource failed."), _T("MF_E_NETWORK_RESOURCE_FAILURE")},
		{0xC00D4269 , _T("Error writing to the network."), _T("MF_E_NET_WRITE")},
		{0xC00D426A , _T("Error reading from the network."), _T("MF_E_NET_READ")},
		{0xC00D426B , _T("Internal. Entry cannot complete operation without network."), _T("MF_E_NET_REQUIRE_NETWORK")},
		{0xC00D426C , _T("Internal. Async op is required."), _T("MF_E_NET_REQUIRE_ASYNC")},
		{0xC00D426D , _T("Internal. Bandwidth levels are not supported."), _T("MF_E_NET_BWLEVEL_NOT_SUPPORTED")},
		{0xC00D426E , _T("Internal. Stream groups are not supported."), _T("MF_E_NET_STREAMGROUPS_NOT_SUPPORTED")},
		{0xC00D426F , _T("Manual stream selection is not supported."), _T("MF_E_NET_MANUALSS_NOT_SUPPORTED")},
		{0xC00D4270 , _T("Invalid presentation descriptor."), _T("MF_E_NET_INVALID_PRESENTATION_DESCRIPTOR")},
		{0xC00D4271 , _T("Cannot find cache stream."), _T("MF_E_NET_CACHESTREAM_NOT_FOUND")},
		{0x400D4272 , _T("The proxy setting is manual."), _T("MF_I_MANUAL_PROXY")},
		{0xC00D4274 , _T("Internal. Entry cannot complete operation without input."), _T("MF_E_NET_REQUIRE_INPUT")},
		{0xC00D4275 , _T("The client redirected to another server."), _T("MF_E_NET_REDIRECT")},
		{0xC00D4276 , _T("The client is redirected to a proxy server."), _T("MF_E_NET_REDIRECT_TO_PROXY")},
		{0xC00D4277 , _T("The client reached maximum redirection limit."), _T("MF_E_NET_TOO_MANY_REDIRECTS")},
		{0xC00D4278 , _T("The server, a computer set up to offer multimedia content to other computers, could not handle your request for multimedia content in a timely manner. Please try again later."), _T("MF_E_NET_TIMEOUT")},
		{0xC00D4279 , _T("The control socket is closed by the client."), _T("MF_E_NET_CLIENT_CLOSE")},
		{0xC00D427A , _T("The server received invalid data from the client on the control connection."), _T("MF_E_NET_BAD_CONTROL_DATA")},
		{0xC00D427B , _T("The server is not a compatible streaming media server."), _T("MF_E_NET_INCOMPATIBLE_SERVER")},
		{0xC00D427C , _T("Url."), _T("MF_E_NET_UNSAFE_URL")},
		{0xC00D427D , _T("Data is not available."), _T("MF_E_NET_CACHE_NO_DATA")},
		{0xC00D427E , _T("End of line."), _T("MF_E_NET_EOL")},
		{0xC00D427F , _T("The request could not be understood by the server."), _T("MF_E_NET_BAD_REQUEST")},
		{0xC00D4280 , _T("The server encountered an unexpected condition which prevented it from fulfilling the request."), _T("MF_E_NET_INTERNAL_SERVER_ERROR")},
		{0xC00D4281 , _T("Session not found."), _T("MF_E_NET_SESSION_NOT_FOUND")},
		{0xC00D4282 , _T("There is no connection established with the Windows Media server. The operation failed."), _T("MF_E_NET_NOCONNECTION")},
		{0xC00D4283 , _T("The network connection has failed."), _T("MF_E_NET_CONNECTION_FAILURE")},
		{0xC00D4284 , _T("The Server service that received the HTTP push request is not a compatible version of Windows Media Services (WMS). This error may indicate the push request was received by IIS instead of WMS. Ensure WMS is started and has the HTTP Server control protocol properly enabled and try again."), _T("MF_E_NET_INCOMPATIBLE_PUSHSERVER")},
		{0xC00D4285 , _T("The Windows Media server is denying access. The username and/or password might be incorrect."), _T("MF_E_NET_SERVER_ACCESSDENIED")},
		{0xC00D4286 , _T("The proxy server is denying access. The username and/or password might be incorrect."), _T("MF_E_NET_PROXY_ACCESSDENIED")},
		{0xC00D4287 , _T("Unable to establish a connection to the server."), _T("MF_E_NET_CANNOTCONNECT")},
		{0xC00D4288 , _T("The specified push template is invalid."), _T("MF_E_NET_INVALID_PUSH_TEMPLATE")},
		{0xC00D4289 , _T("The specified push publishing point is invalid."), _T("MF_E_NET_INVALID_PUSH_PUBLISHING_POINT")},
		{0xC00D428A , _T("The requested resource is in use."), _T("MF_E_NET_BUSY")},
		{0xC00D428B , _T("The Publishing Point or file on the Windows Media Server is no longer available."), _T("MF_E_NET_RESOURCE_GONE")},
		{0xC00D428C , _T("The proxy experienced an error while attempting to contact the media server."), _T("MF_E_NET_ERROR_FROM_PROXY")},
		{0xC00D428D , _T("The proxy did not receive a timely response while attempting to contact the media server."), _T("MF_E_NET_PROXY_TIMEOUT")},
		{0xC00D428E , _T("The server is currently unable to handle the request due to a temporary overloading or maintenance of the server."), _T("MF_E_NET_SERVER_UNAVAILABLE")},
		{0xC00D428F , _T("The encoding process was unable to keep up with the amount of supplied data."), _T("MF_E_NET_TOO_MUCH_DATA")},
		{0xC00D4290 , _T("Session not found."), _T("MF_E_NET_SESSION_INVALID")},
		{0xC00D4291 , _T("The requested URL is not available in offline mode."), _T("MF_E_OFFLINE_MODE")},
		{0xC00D4292 , _T("A device in the network is blocking UDP traffic."), _T("MF_E_NET_UDP_BLOCKED")},
		{0xC00D4293 , _T("The specified configuration value is not supported."), _T("MF_E_NET_UNSUPPORTED_CONFIGURATION")},
		{0xC00D4294 , _T("The networking protocol is disabled."), _T("MF_E_NET_PROTOCOL_DISABLED")},
		{0xC00D4650 , _T("This object has already been initialized and cannot be re-initialized at this time."), _T("MF_E_ALREADY_INITIALIZED")},
		{0xC00D4651 , _T("The amount of data passed in exceeds the given bitrate and buffer window."), _T("MF_E_BANDWIDTH_OVERRUN")},
		{0xC00D4652 , _T("The sample was passed in too late to be correctly processed."), _T("MF_E_LATE_SAMPLE")},
		{0xC00D4653 , _T("The requested action cannot be carried out until the object is flushed and the queue is emptied."), _T("MF_E_FLUSH_NEEDED")},
		{0xC00D4654 , _T("The profile is invalid."), _T("MF_E_INVALID_PROFILE")},
		{0xC00D4655 , _T("The index that is being generated needs to be committed before the requested action can be carried out."), _T("MF_E_INDEX_NOT_COMMITTED")},
		{0xC00D4656 , _T("The index that is necessary for the requested action is not found."), _T("MF_E_NO_INDEX")},
		{0xC00D4657 , _T("The requested index cannot be added in-place to the specified ASF content."), _T("MF_E_CANNOT_INDEX_IN_PLACE")},
		{0xC00D4658 , _T("The ASF leaky bucket parameters must be specified in order to carry out this request."), _T("MF_E_MISSING_ASF_LEAKYBUCKET")},
		{0xC00D4659 , _T("The stream id is invalid. The valid range for ASF stream id is from 1 to 127."), _T("MF_E_INVALID_ASF_STREAMID")},
		{0xC00D4A38 , _T("The requested Stream Sink has been removed and cannot be used."), _T("MF_E_STREAMSINK_REMOVED")},
		{0xC00D4A3A , _T("The various Stream Sinks in this Media Sink are too far out of sync for the requested action to take place."), _T("MF_E_STREAMSINKS_OUT_OF_SYNC")},
		{0xC00D4A3B , _T("Stream Sinks cannot be added to or removed from this Media Sink because its set of streams is fixed."), _T("MF_E_STREAMSINKS_FIXED")},
		{0xC00D4A3C , _T("The given Stream Sink already exists."), _T("MF_E_STREAMSINK_EXISTS")},
		{0xC00D4A3D , _T("Sample allocations have been canceled."), _T("MF_E_SAMPLEALLOCATOR_CANCELED")},
		{0xC00D4A3E , _T("The sample allocator is currently empty, due to outstanding requests."), _T("MF_E_SAMPLEALLOCATOR_EMPTY")},
		{0xC00D4A3F , _T("When we try to sopt a stream sink, it is already stopped "), _T("MF_E_SINK_ALREADYSTOPPED")},
		{0xC00D4A40 , _T("The ASF file sink could not reserve AVIO because the bitrate is unknown."), _T("MF_E_ASF_FILESINK_BITRATE_UNKNOWN")},
		{0xC00D4A41 , _T("No streams are selected in sink presentation descriptor."), _T("MF_E_SINK_NO_STREAMS")},
		{0x000D4A42 , _T("The sink has not been finalized before shut down. This may cause sink generate a corrupted content."), _T("MF_S_SINK_NOT_FINALIZED")},
		{0xC00D4E20 , _T("There is no available procamp hardware with which to perform color correction."), _T("MF_E_VIDEO_REN_NO_PROCAMP_HW")},
		{0xC00D4E21 , _T("There is no available deinterlacing hardware with which to deinterlace the video stream."), _T("MF_E_VIDEO_REN_NO_DEINTERLACE_HW")},
		{0xC00D4E22 , _T("A video stream requires copy protection to be enabled, but there was a failure in attempting to enable copy protection."), _T("MF_E_VIDEO_REN_COPYPROT_FAILED")},
		{0xC00D4E23 , _T("A component is attempting to access a surface for sharing that is not shared."), _T("MF_E_VIDEO_REN_SURFACE_NOT_SHARED")},
		{0xC00D4E24 , _T("A component is attempting to access a shared device that is already locked by another component."), _T("MF_E_VIDEO_DEVICE_LOCKED")},
		{0xC00D4E25 , _T("The device is no longer available. The handle should be closed and a new one opened."), _T("MF_E_NEW_VIDEO_DEVICE")},
		{0xC00D4E26 , _T("A video sample is not currently queued on a stream that is required for mixing."), _T("MF_E_NO_VIDEO_SAMPLE_AVAILABLE")},
		{0xC00D4E84 , _T("No audio playback device was found."), _T("MF_E_NO_AUDIO_PLAYBACK_DEVICE")},
		{0xC00D4E85 , _T("The requested audio playback device is currently in use."), _T("MF_E_AUDIO_PLAYBACK_DEVICE_IN_USE")},
		{0xC00D4E86 , _T("The audio playback device is no longer present."), _T("MF_E_AUDIO_PLAYBACK_DEVICE_INVALIDATED")},
		{0xC00D4E87 , _T("The audio service is not running."), _T("MF_E_AUDIO_SERVICE_NOT_RUNNING")},
		{0xC00D520E , _T("The topology contains an invalid optional node. Possible reasons are incorrect number of outputs and inputs or optional node is at the beginning or end of a segment. "), _T("MF_E_TOPO_INVALID_OPTIONAL_NODE")},
		{0xC00D5211 , _T("No suitable transform was found to decrypt the content. "), _T("MF_E_TOPO_CANNOT_FIND_DECRYPTOR")},
		{0xC00D5212 , _T("No suitable transform was found to encode or decode the content. "), _T("MF_E_TOPO_CODEC_NOT_FOUND")},
		{0xC00D5213 , _T("Unable to find a way to connect nodes"), _T("MF_E_TOPO_CANNOT_CONNECT")},
		{0xC00D5214 , _T("Unsupported operations in topoloader"), _T("MF_E_TOPO_UNSUPPORTED")},
		{0xC00D5215 , _T("The topology or its nodes contain incorrectly set time attributes"), _T("MF_E_TOPO_INVALID_TIME_ATTRIBUTES")},
		{0xC00D61AC , _T("The sequencer cannot find a segment with the given ID.%0\n."), _T("MF_E_SEQUENCER_UNKNOWN_SEGMENT_ID")},
		{0x000D61AD , _T("The context was canceled.%0\n."), _T("MF_S_SEQUENCER_CONTEXT_CANCELED")},
		{0xC00D61AE , _T("Cannot find source in source cache.%0\n."), _T("MF_E_NO_SOURCE_IN_CACHE")},
		{0x000D61AF , _T("Cannot update topology flags.%0\n."), _T("MF_S_SEQUENCER_SEGMENT_AT_END_OF_STREAM")},
		{0xC00D6D60 , _T("A valid type has not been set for this stream or a stream that it depends on."), _T("MF_E_TRANSFORM_TYPE_NOT_SET")},
		{0xC00D6D61 , _T("A stream change has occurred. Output cannot be produced until the streams have been renegotiated."), _T("MF_E_TRANSFORM_STREAM_CHANGE")},
		{0xC00D6D62 , _T("The transform cannot take the requested action until all of the input data it currently holds is processed or flushed."), _T("MF_E_TRANSFORM_INPUT_REMAINING")},
		{0xC00D6D63 , _T("The transform requires a profile but no profile was supplied or found."), _T("MF_E_TRANSFORM_PROFILE_MISSING")},
		{0xC00D6D64 , _T("The transform requires a profile but the supplied profile was invalid or corrupt."), _T("MF_E_TRANSFORM_PROFILE_INVALID_OR_CORRUPT")},
		{0xC00D6D65 , _T("The transform requires a profile but the supplied profile ended unexpectedly while parsing."), _T("MF_E_TRANSFORM_PROFILE_TRUNCATED")},
		{0xC00D6D66 , _T("The property ID does not match any property supported by the transform."), _T("MF_E_TRANSFORM_PROPERTY_PID_NOT_RECOGNIZED")},
		{0xC00D6D67 , _T("The variant does not have the type expected for this property ID."), _T("MF_E_TRANSFORM_PROPERTY_VARIANT_TYPE_WRONG")},
		{0xC00D6D68 , _T("An attempt was made to set the value on a read-only property."), _T("MF_E_TRANSFORM_PROPERTY_NOT_WRITEABLE")},
		{0xC00D6D69 , _T("The array property value has an unexpected number of dimensions."), _T("MF_E_TRANSFORM_PROPERTY_ARRAY_VALUE_WRONG_NUM_DIM")},
		{0xC00D6D6A , _T("The array or blob property value has an unexpected size."), _T("MF_E_TRANSFORM_PROPERTY_VALUE_SIZE_WRONG")},
		{0xC00D6D6B , _T("The property value is out of range for this transform."), _T("MF_E_TRANSFORM_PROPERTY_VALUE_OUT_OF_RANGE")},
		{0xC00D6D6C , _T("The property value is incompatible with some other property or mediatype set on the transform."), _T("MF_E_TRANSFORM_PROPERTY_VALUE_INCOMPATIBLE")},
		{0xC00D6D6D , _T("The requested operation is not supported for the currently set output mediatype."), _T("MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_OUTPUT_MEDIATYPE")},
		{0xC00D6D6E , _T("The requested operation is not supported for the currently set input mediatype."), _T("MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_INPUT_MEDIATYPE")},
		{0xC00D6D6F , _T("The requested operation is not supported for the currently set combination of mediatypes."), _T("MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_MEDIATYPE_COMBINATION")},
		{0xC00D6D70 , _T("The requested feature is not supported in combination with some other currently enabled feature."), _T("MF_E_TRANSFORM_CONFLICTS_WITH_OTHER_CURRENTLY_ENABLED_FEATURES")},
		{0xC00D6D72 , _T("The transform cannot produce output until it gets more input samples."), _T("MF_E_TRANSFORM_NEED_MORE_INPUT")},
		{0xC00D6D73 , _T("The requested operation is not supported for the current speaker configuration."), _T("MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_SPKR_CONFIG")},
		{0xC00D6D74 , _T("The transform cannot accept mediatype changes in the middle of processing."), _T("MF_E_TRANSFORM_CANNOT_CHANGE_MEDIATYPE_WHILE_PROCESSING")},
		{0x000D6D75 , _T("The caller should not propagate this event to downstream components."), _T("MF_S_TRANSFORM_DO_NOT_PROPAGATE_EVENT")},
		{0xC00D6D76 , _T("The input type is not supported for D3D device."), _T("MF_E_UNSUPPORTED_D3D_TYPE")},
		{0xC00D7148 , _T("You are not allowed to open this file. Contact the content provider for further assistance."), _T("MF_E_LICENSE_INCORRECT_RIGHTS")},
		{0xC00D7149 , _T("The license for this media file has expired. Get a new license or contact the content provider for further assistance."), _T("MF_E_LICENSE_OUTOFDATE")},
		{0xC00D714A , _T("You need a license to perform the requested operation on this media file."), _T("MF_E_LICENSE_REQUIRED")},
		{0xC00D714B , _T("The licenses for your media files are corrupted. Contact Microsoft product support."), _T("MF_E_DRM_HARDWARE_INCONSISTENT")},
		{0xC00D714C , _T("The APP needs to provide IMFContentProtectionManager callback to access the protected media file."), _T("MF_E_NO_CONTENT_PROTECTION_MANAGER")},
		{0xC00D714D , _T("Client does not have rights to restore licenses."), _T("MF_E_LICENSE_RESTORE_NO_RIGHTS")},
		{0xC00D714E , _T("Licenses are restricted and hence can not be backed up."), _T("MF_E_BACKUP_RESTRICTED_LICENSE")},
		{0xC00D714F , _T("License restore requires machine to be individualized."), _T("MF_E_LICENSE_RESTORE_NEEDS_INDIVIDUALIZATION")},
		{0x000D7150 , _T("Protection for stream is not required."), _T("MF_S_PROTECTION_NOT_REQUIRED")},
		{0xC00D7151 , _T("Component is revoked."), _T("MF_E_COMPONENT_REVOKED")},
		{0xC00D7152 , _T("Trusted functionality is currently disabled on this component."), _T("MF_E_TRUST_DISABLED")},
		{0xC00D7153 , _T("No Action is set on WMDRM Output Trust Authority."), _T("MF_E_WMDRMOTA_NO_ACTION")},
		{0xC00D7154 , _T("Action is already set on WMDRM Output Trust Authority."), _T("MF_E_WMDRMOTA_ACTION_ALREADY_SET")},
		{0xC00D7155 , _T("DRM Heaader is not available."), _T("MF_E_WMDRMOTA_DRM_HEADER_NOT_AVAILABLE")},
		{0xC00D7156 , _T("Current encryption scheme is not supported."), _T("MF_E_WMDRMOTA_DRM_ENCRYPTION_SCHEME_NOT_SUPPORTED")},
		{0xC00D7157 , _T("Action does not match with current configuration."), _T("MF_E_WMDRMOTA_ACTION_MISMATCH")},
		{0xC00D7158 , _T("Invalid policy for WMDRM Output Trust Authority."), _T("MF_E_WMDRMOTA_INVALID_POLICY")},
		{0xC00D7159 , _T("The policies that the Input Trust Authority requires to be enforced are unsupported by the outputs."), _T("MF_E_POLICY_UNSUPPORTED")},
		{0xC00D715A , _T("The OPL that the license requires to be enforced are not supported by the Input Trust Authority."), _T("MF_E_OPL_NOT_SUPPORTED")},
		{0xC00D715B , _T("The topology could not be successfully verified."), _T("MF_E_TOPOLOGY_VERIFICATION_FAILED")},
		{0xC00D715C , _T("Signature verification could not be completed successfully for this component."), _T("MF_E_SIGNATURE_VERIFICATION_FAILED")},
		{0xC00D715D , _T("Running this process under a debugger while using protected content is not allowed."), _T("MF_E_DEBUGGING_NOT_ALLOWED")},
		{0xC00D715E , _T("MF component has expired."), _T("MF_E_CODE_EXPIRED")},
		{0xC00D715F , _T("The current GRL on the machine does not meet the minimum version requirements."), _T("MF_E_GRL_VERSION_TOO_LOW")},
		{0xC00D7160 , _T("The current GRL on the machine does not contain any renewal entries for the specified revocation."), _T("MF_E_GRL_RENEWAL_NOT_FOUND")},
		{0xC00D7161 , _T("The current GRL on the machine does not contain any extensible entries for the specified extension GUID."), _T("MF_E_GRL_EXTENSIBLE_ENTRY_NOT_FOUND")},
		{0xC00D7162 , _T("The kernel isn't secure for high security level content."), _T("MF_E_KERNEL_UNTRUSTED")},
		{0xC00D7163 , _T("The response from protected environment driver isn't valid."), _T("MF_E_PEAUTH_UNTRUSTED")},
		{0xC00D7165 , _T("A non-PE process tried to talk to PEAuth."), _T("MF_E_NON_PE_PROCESS")},
		{0xC00D7167 , _T("We need to reboot the machine."), _T("MF_E_REBOOT_REQUIRED")},
		{0x000D7168 , _T("Protection for this stream is not guaranteed to be enforced until the MEPolicySet event is fired."), _T("MF_S_WAIT_FOR_POLICY_SET")},
		{0x000D7169 , _T("This video stream is disabled because it is being sent to an unknown software output."), _T("MF_S_VIDEO_DISABLED_WITH_UNKNOWN_SOFTWARE_OUTPUT")},
		{0xC00D716A , _T("The GRL file is not correctly formed, it may have been corrupted or overwritten."), _T("MF_E_GRL_INVALID_FORMAT")},
		{0xC00D716B , _T("The GRL file is in a format newer than those recognized by this GRL Reader."), _T("MF_E_GRL_UNRECOGNIZED_FORMAT")},
		{0xC00D716C , _T("The GRL was reloaded and required all processes that can run protected media to restart."), _T("MF_E_ALL_PROCESS_RESTART_REQUIRED")},
		{0xC00D716D , _T("The GRL was reloaded and the current process needs to restart."), _T("MF_E_PROCESS_RESTART_REQUIRED")},
		{0xC00D716E , _T("The user space is untrusted for protected content play."), _T("MF_E_USERMODE_UNTRUSTED")},
		{0xC00D716F , _T("PEAuth communication session hasn't been started."), _T("MF_E_PEAUTH_SESSION_NOT_STARTED")},
		{0xC00D7170 , _T("Insufficient memory for response."), _T("MF_E_INSUFFICIENT_BUFFER")},
		{0xC00D7171 , _T("PEAuth's public key is revoked."), _T("MF_E_PEAUTH_PUBLICKEY_REVOKED")},
		{0xC00D7172 , _T("The GRL is absent."), _T("MF_E_GRL_ABSENT")},
		{0x000D7173 , _T("The Protected Environment is trusted."), _T("MF_S_PE_TRUSTED")},
		{0xC00D7174 , _T("The Protected Environment is untrusted."), _T("MF_E_PE_UNTRUSTED")},
		{0xC00D7175 , _T("The Protected Environment Authorization service (PEAUTH) has not been started."), _T("MF_E_PEAUTH_NOT_STARTED")},
		{0xC00D7176 , _T("The sample protection algorithms supported by components are not compatible."), _T("MF_E_INCOMPATIBLE_SAMPLE_PROTECTION")},
		{0xC00D7177 , _T("No more protected environment sessions can be supported."), _T("MF_E_PE_SESSIONS_MAXED")},
		{0xC00D7178 , _T("WMDRM ITA does not allow protected content with high security level for this release."), _T("MF_E_HIGH_SECURITY_LEVEL_CONTENT_NOT_ALLOWED")},
		{0xC00D7179 , _T("WMDRM ITA cannot allow the requested action for the content as one or more components is not properly signed."), _T("MF_E_TEST_SIGNED_COMPONENTS_NOT_ALLOWED")},
		{0xC00D717A , _T("WMDRM ITA does not support the requested action."), _T("MF_E_ITA_UNSUPPORTED_ACTION")},
		{0xC00D717B , _T("WMDRM ITA encountered an error in parsing the Secure Audio Path parameters."), _T("MF_E_ITA_ERROR_PARSING_SAP_PARAMETERS")},
		{0xC00D717C , _T("The Policy Manager action passed in is invalid."), _T("MF_E_POLICY_MGR_ACTION_OUTOFBOUNDS")},
		{0xC00D717D , _T("The structure specifying Output Protection Level is not the correct format."), _T("MF_E_BAD_OPL_STRUCTURE_FORMAT")},
		{0xC00D717E , _T("WMDRM ITA does not recognize the Explicite Analog Video Output Protection guid specified in the license."), _T("MF_E_ITA_UNRECOGNIZED_ANALOG_VIDEO_PROTECTION_GUID")},
		{0xC00D717F , _T("IMFPMPHost object not available."), _T("MF_E_NO_PMP_HOST")},
		{0xC00D7180 , _T("WMDRM ITA could not initialize the Output Protection Level data."), _T("MF_E_ITA_OPL_DATA_NOT_INITIALIZED")},
		{0xC00D7181 , _T("WMDRM ITA does not recognize the Analog Video Output specified by the OTA."), _T("MF_E_ITA_UNRECOGNIZED_ANALOG_VIDEO_OUTPUT")},
		{0xC00D7182 , _T("WMDRM ITA does not recognize the Digital Video Output specified by the OTA."), _T("MF_E_ITA_UNRECOGNIZED_DIGITAL_VIDEO_OUTPUT")},
		{0xC00D9C40 , _T("The continuity key supplied is not currently valid."), _T("MF_E_CLOCK_INVALID_CONTINUITY_KEY")},
		{0xC00D9C41 , _T("No Presentation Time Source has been specified."), _T("MF_E_CLOCK_NO_TIME_SOURCE")},
		{0xC00D9C42 , _T("The clock is already in the requested state."), _T("MF_E_CLOCK_STATE_ALREADY_SET")},
		{0xC00D9C43 , _T("The clock has too many advanced features to carry out the request."), _T("MF_E_CLOCK_NOT_SIMPLE")},
		{0x000D9C44 , _T("Timer::SetTimer returns this success code if called happened while timer is stopped. Timer is not going to be dispatched until clock is running"), _T("MF_S_CLOCK_STOPPED")},
		{0xC00DA028 , _T("The component does not support any more drop modes."), _T("MF_E_NO_MORE_DROP_MODES")},
		{0xC00DA029 , _T("The component does not support any more quality levels."), _T("MF_E_NO_MORE_QUALITY_LEVELS")},
		{0xC00DA02A , _T("The component does not support drop time functionality."), _T("MF_E_DROPTIME_NOT_SUPPORTED")},
		{0xC00DA02B , _T("Quality Manager needs to wait longer before bumping the Quality Level up."), _T("MF_E_QUALITYKNOB_WAIT_LONGER")},
		{0xC00DA02C , _T("Quality Manager is in an invalid state. Quality Management is off at this moment."), _T("MF_E_QM_INVALIDSTATE")},
	};
}