
#pragma once
#include "def.h"


class matrix
{
    UINT    	m_nRow;
    UINT    	m_nCol;
    MATDATA*    m_pData;

public:
    matrix(UINT m,UINT n);
    ~matrix();
    matrix(const matrix& mat);
    
    matrix& operator=(const matrix& mat);

    UINT GetRowCount() const;
    UINT GetColCount() const;
    MATRET GetElement(UINT iRow,UINT iCol,MATDATA& rData) const;
    MATRET GetRowData(UINT iRow,MATDATA* pData,UINT nDataLen) const;//pData!=NULL
    MATRET GetColData(UINT iCol,MATDATA* pData,UINT nDataLen) const;//pData!=NULL

    MATRET SetElement(UINT iRow,UINT iCol,MATDATA fData);
    MATRET SetRowData(UINT iRow,const MATDATA* pData,UINT nDataLen);
    MATRET SetColData(UINT iCol,const MATDATA* pData,UINT nDataLen);
    MATRET AppendRow(const MATDATA* pData,UINT nDataLen);
    MATRET AppendCol(const MATDATA* pData,UINT nDataLen);


    static MATRET GetUnitMatrix(UINT m,matrix** pRetmat);
    static MATRET CombineMatrixH(const matrix& mat1,const matrix& mat2,matrix** pRetmat);
    static MATRET CombineMatrixV(const matrix& mat1,const matrix& mat2,matrix** pRetmat);
	static MATRET MatrixAdd(const matrix& mat1,const matrix& mat2,matrix** pRetmat);
	static MATRET MatrixSub(const matrix& mat1,const matrix& mat2,matrix** pRetmat);
	static MATRET MatrixMUl(const matrix& mat1,const matrix& mat2,matrix** pRetmat);
	
};
