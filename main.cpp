#include <iostream>
#include <regex>
#include <string>
#include <map>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

using namespace std;
namespace pt = boost::property_tree;
const std::string xsd_path = "./sep.xsd";
const std::string wadl_path = "./sep_wadl.xml";

std::string abbreviate (const std::string& word)
{
    std::string abbreviation;
    for (const auto& letter : word)
    {
        if (isupper(letter))
        {
            abbreviation = abbreviation + letter;
        }
    }
    return abbreviation;
};

void propertyTreeTraversal(
    const int depth,
    const pt::ptree& tree,
    std::map <std::string, std::string>* table
    )
{
    BOOST_FOREACH(const auto& node, tree.get_child("") ) {
        pt::ptree subtree = node.second;
        string nodestr = tree.get<string>(node.first);

        // print current node
        if (node.first == "name")
        {
            std::string value = tree.get<string>("default", "");
            (*table)[tree.get<string>(node.first)] = value;
        }

        // recursive go down the hierarchy
        propertyTreeTraversal(depth+1,subtree, table);
    }
};

void printDuplicates(std::vector <std::string> words)
{
    std::vector <std::string> duplicate;

    // STL function to sort the array of string
    sort(words.begin(), words.end());

    for (unsigned int i = 1; i<words.size(); i++)
        if (words[i-1] == words[i])

            // STL function to push the duplicate
            // words in a new vector string
            duplicate.push_back(words[i]);

    unsigned int i = 0;
    for (i = 0; i<duplicate.size(); i++)
            cout << duplicate[i] << endl;

    if (i == 0)
        cout << "No Duplicate words" << endl;
}

void parseXSD ()
{
    pt::ptree sep;
    pt::read_xml(xsd_path, sep );

    BOOST_FOREACH (const auto& node, sep.get_child ("xs:schema")
    )
    {
        if (node.first == "xs:complexType")
        {
            pt::ptree child = node.second;
            std::string name = child.get <std::string> ("<xmlattr>.name", "");
            cout << name << endl;

            std::map <std::string, std::string> table;
            propertyTreeTraversal(0, child,&table);

            for (const auto& it : table)
            {
                cout << "\t" << it.first << " = " << it.second << "\n";
            }
            cout << endl;
        }
    }
}

void parseWADL ()
{
    pt::ptree wadl;
    pt::read_xml(wadl_path, wadl );
    std::vector <std::string> paths;
    BOOST_FOREACH (const auto& node, wadl.get_child ("application.resources")
    )
    {
        if (node.first == "resource")
        {
            pt::ptree child = node.second;
            std::string name = child.get <std::string> ("<xmlattr>.id", "");
            std::string path = child.get <std::string> ("<xmlattr>.wx:samplePath", "");
            cout << name <<  " : " << path << endl;
            paths.push_back(path);

            std::regex path_rx(R"([^/]+)");
            std::smatch parts;

            // finding all the match.
            unsigned int i = 1;
            std::string subject = path;
            while (std::regex_search(subject, parts, path_rx)) {
                cout << "\nMatched string is " << parts.str(0) << endl;
                i++;

                // suffix to find the rest of the string.
                subject = parts.suffix().str();
            }

            std::map <std::string, std::string> table;
            propertyTreeTraversal(0, child,&table);

            for (const auto& it : table)
            {
                cout << "\t" << it.first << " = " << it.second << "\n";
            }
            cout << endl;
        }
    }
    printDuplicates(paths);
}

namespace sep {
    typedef bool boolean;
    using int = int;
};


int main()
{

    //parseWADL();
    //Time tm();
    sep::boolean x = false;
    sep::int y = 292929292;
    cout << y << endl;
    return 0;
}
