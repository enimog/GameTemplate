#pragma once

#include <vector>
#include "File.h"

namespace File
{
    class CCSVFile : public File
    {
    public:
        /*
         * CSV Constructor
         * 
         * @param : path and name of the file you want to use
         */
        explicit CCSVFile( std::wstring const& path );

        /*
        * Add a value to a specific row to the csv file
        *
        * @param : row index
        * @param : value to add
        *
        */
        void Add( size_t row, std::wstring const& value ) const;

        /*
        * Add an empty row to the csv file
        */
        void AddRow() const;

        /*
        * Remove a value to a specific row to the csv file
        *
        * @param : row index
        * @param : column index
        *
        */
        void Remove( size_t row, size_t column ) const;

        /*
        * [] get operator
        *
        * enable to get a row of the CSV file
        * @param : row index
        * @return : all the values for a specific row
        *
        */
        std::vector<std::wstring> operator []( size_t row ) const;

        /*
         * Return the number of rows the csv file contain
         * 
         * @return : number of rows
         */
        size_t row() const;

    private:
        /*
         * Separator symbol used in the csv file
         */
        const wchar_t separator;

        /*
         * Cache value for the last row returned by []
         */
        mutable std::vector<std::wstring> LastRow;

        /*
        * Cache index for the last row returned by []
        */
        mutable size_t LastRowIndex;
    };
}
