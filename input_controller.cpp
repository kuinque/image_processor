#include "input_controller.h"

// reads file input
void InputController::InputFlow(const int argc, char* argv[]) {
    if (argc == 1) {
        InputInfo();
        return;
    }
    if (argc == 2) {
        throw std::runtime_error("Output path didn't specifyed.");
    }
    std::string input_path = argv[1];
    std::string output_path = argv[2];
    BMPImage image;
    image.Open(input_path);
    image.ReadBmp();
    pixel_array_ = image.GetMatrixReference();
    InputAnalyze(argc, argv);
    image.SaveBmp(output_path);
}

// outputs info about filters
void InputController::InputInfo() {
    std::cout << "{name of program} {input path} {output path} [-{name of filter 1} [filter param 1] [filter param "
                 "2] ...] [-{name of filter 2} [filter param 1] [filter param 2] ...] ..."
              << std::endl;
    std::cout << "[h] filters:" << std::endl;
    std::cout << "[-crop] [new width] [new height] - crop image to left upper corner" << std::endl;
    std::cout << "[-gs] - shades of gray" << std::endl;
    std::cout << "[-neg] - negtive image" << std::endl;
    std::cout << "[-sharp] - improves sharpness" << std::endl;
    std::cout << "[-edge] [threshold] - edge detection" << std::endl;
    std::cout << "[-blur] [sigma] - gaussian blur" << std::endl;
    std::cout << "[-retro] - retro filter" << std::endl;
}

// analyze parametrs and filters
void InputController::InputAnalyze(const int argc, char* argv[]) {
    for (int argc_num = 3; argc_num < argc; ++argc_num) {
        if (argv[argc_num][0] != '-') {
            throw std::runtime_error("Filter name should begin from -.");
        }
        if (filter_map_.find(argv[argc_num]) == filter_map_.end()) {
            throw std::runtime_error("Wrong filter name.");
        }
        int parametr_num = 0;
        while (argc_num + parametr_num + 1 < argc && argv[argc_num + parametr_num + 1][0] != '-') {
            ++parametr_num;
        }
        std::string filter_name = argv[argc_num];
        if (filter_name == "-crop") {
            Crop crop{pixel_array_};
            crop.ApplyFilter(parametr_num, argv + argc_num + 1);
        }
        if (filter_name == "-gs") {
            GS gs{pixel_array_};
            gs.ApplyFilter(parametr_num, argv + argc_num + 1);
        }
        if (filter_name == "-neg") {
            Neg neg{pixel_array_};
            neg.ApplyFilter(parametr_num, argv + argc_num + 1);
        }
        if (filter_name == "-sharp") {
            Sharp sharp{pixel_array_};
            sharp.ApplyFilter(parametr_num, argv + argc_num + 1);
        }
        if (filter_name == "-edge") {
            Edge edge{pixel_array_};
            edge.ApplyFilter(parametr_num, argv + argc_num + 1);
        }
        if (filter_name == "-blur") {
            Blur blur{pixel_array_};
            blur.ApplyFilter(parametr_num, argv + argc_num + 1);
        }
        if (filter_name == "-retro") {
            Retro retro{pixel_array_};
            retro.ApplyFilter(parametr_num, argv + argc_num + 1);
        }
        argc_num += parametr_num;
    }
}
