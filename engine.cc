#include <ctime>

#include "easy_image/easy_image.h"
#include "ini_configuration/ini_configuration.h"

#include "headers/input.h"
#include "headers/2DLSystems.h"


img::EasyImage generate_image(const ini::Configuration &configuration)
{
    // Vars
    int start_time = clock();
    img::EasyImage image;

    // Read in our ini file.
    ImageInfo *info = new ImageInfo(configuration);


    // 2D L-Systemen
    if (info->getType() == LSys2D) {

        LSystem2D LS2D = LSystem2D(info);
        image = LS2D.GenerateImage();
    }


    // Write to file. - if needed
    std::ofstream fout("out.bmp", std::ios::binary);
    fout << image;
    fout.close();

    // Display runtime
    int elapsed_time_ms = (clock() - start_time) / double(CLOCKS_PER_SEC) * 1000;
    cout << "RUNTIME: \n" << elapsed_time_ms << " milliseconds" << endl;


    // Cleanup and return result.
    delete info;
	return image;
}


// Do not change.

/*
 * DO NOT FORGET:
 * REMOVE HARDCODED PATHS
 * */

int main(int argc, char const* argv[])
{
    /* testing */
    argc = 2;
    argv[1] = "../examples/ls2d/l_systemsTEST.ini";
    /* end */
    int retVal = 0;
    try
    {

        for(int i = 1; i < argc; ++i)
        {
            ini::Configuration conf;
            try
            {
                std::ifstream fin(argv[i]);
                fin >> conf;
                fin.close();
            }
            catch(ini::ParseException& ex)
            {
                std::cerr << "Error parsing file: " << argv[i] << ": " << ex.what() << std::endl;
                retVal = 1;
                continue;
            }

            img::EasyImage image = generate_image(conf);
            if(image.get_height() > 0 && image.get_width() > 0)
            {
                std::string fileName(argv[i]);
                std::string::size_type pos = fileName.rfind('.');
                if(pos == std::string::npos)
                {
                    //filename does not contain a '.' --> append a '.bmp' suffix
                    fileName += ".bmp";
                }
                else
                {
                    fileName = fileName.substr(0,pos) + ".bmp";
                }
                try
                {
                    std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
                    f_out << image;

                }
                catch(std::exception& ex)
                {
                    std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                    retVal = 1;
                }
            }
            else
            {
                std::cout << "Could not generate image for " << argv[i] << std::endl;
            }
        }
    }
    catch(const std::bad_alloc &exception)
    {
        //When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
        //Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
        //(Unless of course you are already consuming the maximum allowed amount of memory)
        //If your engine does NOT adhere to this requirement you risk losing points because then our scripts will
        //mark the test as failed while in reality it just needed a bit more memory
        std::cerr << "Error: insufficient memory" << std::endl;
        retVal = 100;
    }
    return retVal;
}
