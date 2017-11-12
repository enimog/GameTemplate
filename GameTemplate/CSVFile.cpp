#include "stdafx.h"
#include "CSVFile.h"
#include "FileToolbox.h"

namespace File
{
    CCSVFile::CCSVFile( std::wstring const & path ) : 
        File( Toolbox::FileToolbox::SetExtension( path, L"csv" ) ), 
        separator(L';'),
        LastRowIndex( INFINITE )
    {
    }

    void CCSVFile::Add( size_t row, std::wstring const& value ) const
    {
        auto dataToWrite = getData();

        // Add rows if necessary
        if (dataToWrite.size() <= row)
        {
            dataToWrite.resize( row + 1 );
        }

        // Add separator
        if (dataToWrite[row].size() > 0)
        {
            dataToWrite[row] += L";";
        }

        dataToWrite[row] += L"\"" + value + L"\"";

        setData( dataToWrite );
    }

    void CCSVFile::AddRow() const
    {
        auto dataToWrite = getData();

        dataToWrite.push_back(L"");

        setData( dataToWrite );
    }

    void CCSVFile::Remove( size_t row, size_t column ) const
    {
        auto dataToWrite = getData();

        size_t start = 0;
        
        // Data is stored in the form of "...";"...";"..."
        auto temporary = Toolbox::StringToolbox::Split( dataToWrite[row], separator );
        temporary.erase( temporary.begin() + column );

        // Rebuild data string
        dataToWrite[row] = L"";
        for (auto const& value : temporary)
        {
            // Add separator
            if (dataToWrite[row].size() > 0)
            {
                dataToWrite[row] += L";";
            }

            dataToWrite[row] += L"\"" + value + L"\"";
        }

        setData( dataToWrite );
    }

    std::vector<std::wstring> CCSVFile::operator[]( size_t row ) const
    {
        if (LastRowIndex == row)
        {
            return LastRow;
        }

        // Data is stored in the form of "...";"...";"..."
        auto result = Toolbox::StringToolbox::Split( getData()[row], separator );

        // Remove the " "
        for (auto& value : result)
        {
            value = value.substr( 1, value.size() - 2 );
        }

        LastRow = result;
        LastRowIndex = row;

        return result;
    }

    size_t CCSVFile::row() const
    {
        return getData().size();
    }
}