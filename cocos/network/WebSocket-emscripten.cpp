//
//  EmscriptenWebSocket.cpp
//  cocos2d_libs
//
//  Created by 孙晓群 on 2021/3/8.
//

#include "WebSocket-emscripten.h"
#include "base/CCConsole.h"

namespace cocos2d { namespace network {

WebSocket::WebSocket()
{
    _socket = 0;
    _delegate = 0;
}
bool WebSocket::init(const WebSocket::Delegate& delegate,
          const std::string& url,
          const std::vector<std::string>* protocols,
          const std::string& caFilePath)
{
    _delegate = const_cast<Delegate*>(&delegate);
    _url = url;

    EmscriptenWebSocketCreateAttributes attr;
	emscripten_websocket_init_create_attributes(&attr);
	attr.url = url.c_str();
    
    _selectedProtocol = "";
    if(!protocols->empty())
    {
        for (size_t i = 0; i < protocols->size(); i++)
        {
            _selectedProtocol += protocols->at(i);
            if(i < protocols->size()-1)
                _selectedProtocol += ",";
        }
        
        attr.protocols = _selectedProtocol.c_str();
    }


	_socket = emscripten_websocket_new(&attr);
	if (_socket <= 0)
	{
		CCLOG("WebSocket creation failed, error code %d!\n", (EMSCRIPTEN_RESULT)_socket);
		return false;
	}
	emscripten_websocket_set_onopen_callback(_socket, this
    , [](int eventType, const EmscriptenWebSocketOpenEvent *e, void *userData)->EM_BOOL{
        WebSocket* ws = (WebSocket*)userData;
        ws->_delegate->onOpen(ws);
        return 1;
    });

	emscripten_websocket_set_onclose_callback(_socket, this
    , [](int eventType, const EmscriptenWebSocketCloseEvent *e, void *userData)->EM_BOOL{
        WebSocket* ws = (WebSocket*)userData;
        ws->_delegate->onClose(ws);
        return 1;
    });

    emscripten_websocket_set_onerror_callback(_socket, this
    , [](int eventType, const EmscriptenWebSocketErrorEvent *e, void *userData)->EM_BOOL{
        WebSocket* ws = (WebSocket*)userData;
        ws->_delegate->onError(ws,ErrorCode::CONNECTION_FAILURE);
        return 1;
    });

    emscripten_websocket_set_onmessage_callback(_socket, this
    , [](int eventType, const EmscriptenWebSocketMessageEvent *e, void *userData)->EM_BOOL{
        WebSocket* ws = (WebSocket*)userData;
        Data data;
        data.bytes = (char*)e->data;
        data.len = e->numBytes;
        data.isBinary = e->isText == 0;
        ws->_delegate->onMessage(ws,data);
        return 1;
    });
    return  true;
}


void WebSocket::send(const std::string& message)
{
    if(_socket <= 0)
        return ;
    emscripten_websocket_send_utf8_text(_socket, message.c_str());
}
void WebSocket::send(const unsigned char* binaryMsg, unsigned int len)
{
    emscripten_websocket_send_binary(_socket, (void *)binaryMsg,len);
}

void WebSocket::close()
{
    closeAsync();
}
void WebSocket::closeAsync()
{
    emscripten_websocket_close(_socket,0,0);
    emscripten_websocket_delete(_socket);
    _socket = 0;
}

WebSocket::State WebSocket::getReadyState()
{
    uint16_t readyState = 0;
    emscripten_websocket_get_ready_state(_socket, &readyState);
    return (WebSocket::State)readyState;
}

}}
