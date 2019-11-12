//-- This function loads features stored in a text file
//-- Every feature takes 1 line, and its values separated by a space
Mat LoadFeaturesFromTextFile(string filename)
{
    std::ifstream file(filename);
    
    std::string   line;
    
    Mat features;
    
    // Read one line at a time into the variable line:
    while(std::getline(file, line))
    {
        std::vector<float>   lineData;
        std::stringstream  lineStream(line);
        
        float value;
        // Read a float at a time from the line
        while(lineStream >> value)
        {
            // Add the float from a line to a 1D array (vector)
            lineData.push_back(value);
        }
        
        Mat aux(1, (int)lineData.size(), CV_32FC1, lineData.data());
        features.push_back(aux);
    }
    
    return features;
}


//-- This function loads text stored in a text file
//-- Every text takes 1 line
std::vector<std::string> LoadTextFromTextFile(string filename)
{
    std::ifstream file(filename);
    
    std::string   line;
    
    std::vector<std::string> features;
    
    // Read one line at a time into the variable line:
    while(std::getline(file, line))
    {
        features.push_back(line)
    }
    
    return features;
}