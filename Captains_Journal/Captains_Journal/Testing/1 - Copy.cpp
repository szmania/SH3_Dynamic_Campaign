#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

struct FindWindowData {
    FindWindowData( TCHAR const * windowTitle )
        : WindowTitle( windowTitle )
        , ResultHandle( 0 )
    {}

    std::basic_string<TCHAR> WindowTitle;
    HWND ResultHandle;
};

BOOL CALLBACK FindWindowImpl( HWND hWnd, LPARAM lParam ) {
    FindWindowData * p = reinterpret_cast<FindWindowData*>( LongToPtr( lParam ) );
    if( !p ) {
        // Finish enumerating we received an invalid parameter
        return FALSE;
    }

    int length = GetWindowTextLength( hWnd ) + 1;
    if( length > 0 ) {
        std::vector<TCHAR> buffer( std::size_t( length ), 0 );
        if( GetWindowText( hWnd, &buffer[0], length ) ) {
                    // Comparing the string - If you want to add some features you can do it here
            if( tcsnicmp( &buffer[0], p->WindowTitle.c_str(), min( buffer.size(), p->WindowTitle.size() )  ) == 0 ) {
                p->ResultHandle = hWnd;
                // Finish enumerating we found what we need
                return FALSE;
            }
        }
    }
    // Continue enumerating
    return TRUE;
}

// Returns the window handle when found if it returns 0 GetLastError() will return more information
HWND FindWindowStart( TCHAR const * windowTitle ) {

    if( !windowTitle ) {
        SetLastError( ERROR_INVALID_PARAMETER );
        return 0;
    }

    FindWindowData data( windowTitle );
    if( !EnumWindows( FindWindowImpl, PtrToLong(&data) ) && data.ResultHandle != 0 ) {
        SetLastError( ERROR_SUCCESS );
        return data.ResultHandle;
    }

    // Return ERROR_FILE_NOT_FOUND in GetLastError
    SetLastError( ERROR_FILE_NOT_FOUND );
    return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
    std::cout << "HWND: " << FindWindowStart(TEXT("SilentHunter3") );
    std::cout << "  GetLastError() = " << GetLastError() << std::endl;
    return 0;
}
