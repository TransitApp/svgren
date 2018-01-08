#include "../../src/svgren/render.hpp"

#include <chrono>

#include <utki/debug.hpp>
#include <utki/config.hpp>

#include <papki/FSFile.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <png.h>

#if M_OS == M_OS_LINUX
# include <X11/Xlib.h>
# include <X11/Xutil.h>
#endif



int writePng(const char* filename, int width, int height, std::uint32_t *buffer)
{
    int code = 0;
    FILE *fp = NULL;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    
    // Open file for writing (binary mode)
    fp = fopen(filename, "w+b");
    if (fp == NULL) {
        fprintf(stderr, "Could not open file %s for writing\n", filename);
        code = 1;
        throw utki::Exc("Could not open file for writing");
    }
    
    // Initialize write structure
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
        fprintf(stderr, "Could not allocate write struct\n");
        code = 1;
        throw utki::Exc("Could not allocate write struct");
    }
    
    // Initialize info structure
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fprintf(stderr, "Could not allocate info struct\n");
        code = 1;
        throw utki::Exc("Could not allocate info struct");
    }
    
    png_init_io(png_ptr, fp);
    
    // Write header (8 bit colour depth)
    png_set_IHDR(png_ptr, info_ptr, width, height,
                 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    
    
    png_write_info(png_ptr, info_ptr);
    
    // Write image data
    int y;
    auto p = buffer;
    for (y=0 ; y<height ; y++, p += width) {
        png_write_row(png_ptr, reinterpret_cast<png_bytep>(p));
    }
    
    // End write
    png_write_end(png_ptr, NULL);
    
    if (fp != NULL) fclose(fp);
    if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
    
    return code;
}

namespace{
    std::uint32_t getTicks(){
        return std::uint32_t(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
    }
}


int main(int argc, char **argv){
    std::string filename;
    std::string outFilename;
    
    std::vector<std::string> filenames;
    switch(argc){
        case 0:
        case 1:
            std::cout << "Warning: 2 arguments expected: <in-svg-file> <out-png-file>" << std::endl;
            std::cout << "\t Got 0 arguments, assume <in-svg-file>=tiger <out-png-file>=tiger.png" << std::endl;
            filename = "tiger";
            outFilename = "tiger.png";
            break;
        case 2:
            std::cout << "Warning: 2 arguments expected: <in-svg-file> <out-png-file>" << std::endl;
            filename = argv[1];
        {
            auto dotIndex = filename.find_last_of(".", filename.size());
            if(dotIndex == std::string::npos){
                dotIndex = filename.size();
            }
            outFilename = filename.substr(0, dotIndex) + ".png";
        }
            std::cout << "\t Got 1 argument, assume <in-svg-file>=" << filename << " <out-png-file>=" << outFilename << std::endl;
            break;
        default:
            filename = argv[1];
            outFilename = argv[2];
            break;
    }
    
    std::vector<std::string> filenamesString = {
        "amat-m1",
        "amat-m3",
        "amat-m5",
        "amt-train",
        "amt-train",
        "amt-train",
        "atac-fr1",
        "atac-fr2",
        "atac-fr3",
        "atac-fr4",
        "atac-fr5",
        "atac-fr6",
        "atac-fr7",
        "atac-fr8",
        "austin-metro-rail",
        "austin-metro-rail",
        "austin-metro-rail",
        "caltrain",
        "caltrain",
        "caltrain",
        "dcc",
        "dcc",
        "dcc",
        "hvv-a1",
        "hvv-a2",
        "hvv-a3",
        "hvv-ferry",
        "hvv-ferry",
        "hvv-ferry",
        "hvv-s1",
        "hvv-s21",
        "hvv-s3",
        "hvv-s31",
        "hvv-u3",
        "hvv-u3",
        "hvv-u3",
        "la-metro",
        "la-metro",
        "la-metro",
        "miami-rail",
        "miami-rail",
        "miami-rail",
        "muni-bullet-k2",
        "muni-bullet-l",
        "muni-bullet-m",
        "muni-bullet-n",
        "muni-bullet-t2",
        "muni-cablecar-full",
        "muni-cablecar-full",
        "muni-cablecar-full",
        "path",
        "path",
        "path",
        "ratp-a",
        "ratp-b",
        "ratp-c",
        "ratp-metro-10-v2",
        "ratp-metro-3bis-v2",
        "ratp-metro-3bis-v2",
        "ratp-metro-5-v2",
        "ratp-metro-6-v2",
        "ratp-metro-7-v2",
        "ratp-metro-7bis-v2",
        "ratp-metro-8-v2",
        "ratp-metro-9-v2",
        "ratp-rer-a",
        "ratp-rer-b",
        "skytrain",
        "skytrain",
        "skytrain",
        "sncf-transilien-h",
        "sncf-transilien-j",
        "sncf-transilien-k",
        "sncf-transilien-l",
        "sncf-transilien-n",
        "sncf-transilien-p",
        "sncf-transilien-r",
        "sncf-transilien-u",
        "stif-tram-1-logo",
        "stif-tram-2-logo",
        "stif-tram-3a-logo",
        "stif-tram-3b-logo",
        "stif-tram-4-logo",
        "stif-tram-5-logo",
        "stif-tram-6-logo",
        "stif-tram-7-logo",
        "stif-tram-8-logo",
        "stif-tram-logo",
        "tcl-bus-r1",
        "tcl-bus-r2",
        "tcl-bus-r3",
        "tcl-bus-r5",
        "tcl-bus-zi8",
        "tcl-bus-zi8",
        "tcl-bus-zi8",
        "tcl-resago-logo",
        "tcl-resago-logo",
        "tcl-resago-logo",
        "trenit-s-s1",
        "trenit-s-s10",
        "trenit-s-s11",
        "trenit-s-s13",
        "trenit-s-s2",
        "trenit-s-s3",
        "trenit-s-s3",
        "trenit-s-s3",
        "trenit-s-s4",
        "trenit-s-s5",
        "trenit-s-s6",
        "trenit-s-s8",
        "trenit-s-s9",
        "ttc-subway-2",
        "vbb-ferry",
    };
    
    std::string prefix = "/Users/gdorion/Documents/Code/Transit/svg_images/download/";
    
    for (std::string s : filenamesString) {
        filename = prefix + s + ".svg";
        outFilename = "/Users/gdorion/Documents/Code/Transit/svg_images/pngs/" + s + ".png";
        
        auto loadStart = getTicks();
        
        auto dom = svgdom::load(papki::FSFile(filename));
        ASSERT_ALWAYS(dom)
        
        TRACE(<< "SVG loaded in " << float(getTicks() - loadStart) / 1000.0f << " sec." << std::endl)
        
        
        auto renderStart = getTicks();
        
        unsigned imWidth = 0;
        unsigned imHeight = 0;
        auto img = svgren::render(*dom, imWidth, imHeight);
        
        TRACE(<< "SVG rendered in " << float(getTicks() - renderStart) / 1000.0f << " sec." << std::endl)
        
        TRACE(<< "imWidth = " << imWidth << " imHeight = " << imHeight << " img.size() = " << img.size() << std::endl)
        
        writePng(outFilename.c_str(), imWidth, imHeight, &*img.begin());
        
        
#if M_OS == M_OS_LINUX
        int width = imWidth + 2;
        int height = imHeight + 2;
        
        Display *display = XOpenDisplay(NULL);
        
        Visual *visual = DefaultVisual(display, 0);
        
        Window window = XCreateSimpleWindow(display, RootWindow(display, 0), 0, 0, width, height, 1, 0, 0);
        
        if(visual->c_class != TrueColor){
            TRACE_ALWAYS(<< "Cannot handle non true color visual ...\n" << std::endl)
            return 1;
        }
        
        XSelectInput(display, window, ButtonPressMask|ExposureMask);
        
        XMapWindow(display, window);
        
        while(true){
            XEvent ev;
            XNextEvent(display, &ev);
            switch(ev.type)
            {
                case Expose:
                {
                    int dummyInt;
                    unsigned dummyUnsigned;
                    Window dummyWindow;
                    unsigned imWidth = 0;
                    unsigned imHeight = 0;
                    
                    XGetGeometry(display, window, &dummyWindow, &dummyInt, &dummyInt, &imWidth, &imHeight, &dummyUnsigned, &dummyUnsigned);
                    
                    imWidth = std::max(int(imWidth) - 2, 0);
                    imHeight = std::max(int(imHeight) - 2, 0);
                    
                    //                TRACE(<< "imWidth = " << imWidth << " imHeight = " << imHeight << std::endl)
                    
                    auto img = svgren::render(*dom, imWidth, imHeight);
                    
                    //                TRACE(<< "imWidth = " << imWidth << " imHeight = " << imHeight << " img.size() = " << img.size() << std::endl)
                    
                    auto ximage = XCreateImage(display, visual, 24, ZPixmap, 0, reinterpret_cast<char*>(&*img.begin()), imWidth, imHeight, 8, 0);
                    utki::ScopeExit scopeexit([ximage](){
                        ximage->data = nullptr;//Xlib will try to deallocate data which is owned by 'img' variable.
                        XDestroyImage(ximage);
                    });
                    
                    XPutImage(display, window, DefaultGC(display, 0), ximage, 0, 0, 1, 1, imWidth, imHeight);
                }
                    break;
                case ButtonPress:
                    exit(0);
            }
        }
#endif
    }
    
    
    
    TRACE_ALWAYS(<< "[PASSED]" << std::endl)
}


