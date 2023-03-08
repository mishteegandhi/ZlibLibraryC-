#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <zlib.h>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string compress (const string& str, int compressionlevel = Z_BEST_COMPRESSION)
{
    z_stream zs;
    memset(&zs, 0, sizeof(zs));
    if (deflateInit(&zs, compressionlevel) != Z_OK) throw(runtime_error("deflateInit failed while compressing."));
    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();
    int ret;
    char outbuffer[32768];
    string outstring;
    do
    {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);
        ret = deflate(&zs, Z_FINISH);
        if (outstring.size() < zs.total_out)
        {
            outstring.append(outbuffer, zs.total_out - outstring.size());
        }
    } while (ret == Z_OK);
    deflateEnd(&zs);
    if (ret != Z_STREAM_END)
    {
        ostringstream oss;
        oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
        throw(runtime_error(oss.str()));
    }
    return outstring;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string decompress (const string& str)
{
    z_stream zs;
    memset(&zs, 0, sizeof(zs));
    if (inflateInit(&zs) != Z_OK) throw(runtime_error("inflateInit failed while decompressing."));
    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();
    int ret;
    char outbuffer[32768];
    string outstring;
    do
    {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);
        ret = inflate(&zs, 0);
        if (outstring.size() < zs.total_out)
        {
            outstring.append(outbuffer, zs.total_out - outstring.size());
        }

    } while (ret == Z_OK);

    inflateEnd(&zs);

    if (ret != Z_STREAM_END)
    {
        ostringstream oss;
        oss << "Exception during zlib decompression: (" << ret << ") "  << zs.msg;
        throw(runtime_error(oss.str()));
    }

    return outstring;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    while (1)
    {
        cout << "Please choose what you wish to do:\n1.Compress an input\n2.Decompress an input\n3.Exit program" << endl;
        int choice, cs;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Would you like to input\n1.File\n2.String" << endl;
            cin >> cs;
            switch (cs)
            {
            case 1:
                {
                    ifstream files;
                    string name, o;
                    cout << "Enter filename with extension (.txt): ";
                    cin >> name;
                    files.open(name);
                    string allinput;
                    char ch;
                    if (files.is_open())
                    {
                        while (files)
                        {
                            ch = files.get();
                            allinput = allinput + ch;
                        }
                    }
                    cout << "The inputed information on file is:" << endl << allinput << endl;
                    cout << "\nThe size at input is: " << allinput.size() << endl;
                    string comp = compress(allinput);
                    cout << "The size of compressed information is: " << comp.size() << endl;
                    cout << "\nDo you want to see the compressed information and store it in a new file?(Note compressed information will not be stored otherwise.) (y/n): ";
                    cin >> o;
                    if (o == "y")
                    {
                        cout << "The compressed information is:" << endl << comp << endl;
                        ofstream cfile ("Compressedfile.txt");
                        cfile << comp;
                        cout << "\nName of file created is Compressedfile.txt\n" << endl;
                    }
                }
                break;
            case 2:
                {
                    cout << "Enter string to compress:" << endl;
                    string in;
                    cin >> in;
                    cout << "\nThe size at input is: " << in.size() << endl;
                    string com = compress(in);
                    cout << "The size of compressed information is: " << com.size() << "\n" << endl;
                }
                break;
            }
            break;
        case 2:
            cout << "Would you like to input\n1.File\n2.String" << endl;
            cin >> cs;
            switch (cs)
            {
            case 1:
                {
                    ifstream files;
                    string name, o;
                    cout << "Enter filename with extension (.txt): ";
                    cin >> name;
                    files.open(name);
                    string allinput;
                    char ch;
                    if (files.is_open())
                    {
                        while (files)
                        {
                            ch = files.get();
                            allinput = allinput + ch;
                        }
                    }
                    cout << "The inputed information on file is:" << endl << allinput << endl;
                    cout << "\nThe size at input is: " << allinput.size() << endl;
                    string decomp = decompress(allinput);
                    cout << "\nThe decompressed information is:" << endl << decomp << endl;
                    cout << "\nThe size of decompressed information is: " << decomp.size() << endl;
                    cout << "Do you want to store the decompressed information in a new file?(Note decompressed information will not be stored otherwise.) (y/n): ";
                    cin >> o;
                    if (o == "y")
                    {
                        ofstream dfile ("Decompressedfile.txt");
                        dfile << decomp;
                        cout << "Name of file created is Decompressedfile.txt\n" << endl;
                    }
                }
                break;
            case 2:
                {
                    cout << "Enter string to decompress:" << endl;
                    string in;
                    cin >> in;
                    cout << "The size at input is: " << in.size() << endl;
                    string decom = decompress(in);
                    cout << "The size of decompressed information is: " << decom.size() << "\n"<< endl;
                }
                break;
            }
            break;
        case 3:
            cout << "Exit program";
            return 0;
            break;
        }
    }
}
