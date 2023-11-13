void splitString(const string &inputString, vector<string> &outputVector, char delimiter)
    {
        istringstream tokenStream(inputString);
        string token;

        while (getline(tokenStream, token, delimiter))
        {
            outputVector.push_back(token);
        }
    }