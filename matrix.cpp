
#include "matrix.h"
#include <memory.h>

#include <iostream>

matrix::matrix(UINT m,UINT n)
{
    m_nRow=m;
    m_nCol=n;
    if(m*n==0)
    {
    	m_pData=NULL;
    }
    else
    {
    	m_pData=new MATDATA[m*n];
    	memset(m_pData,0,sizeof(MATDATA)*m*n);
    }
}

matrix::matrix(const matrix& mat)
{
	m_nRow=mat.m_nRow;
	m_nCol=mat.m_nCol;
	if(m_nRow*m_nCol>0)
	{
		m_pData=new MATDATA[m_nRow*m_nCol];
		memcpy(m_pData,mat.m_pData,sizeof(MATDATA)*m_nRow*m_nCol);
	}
	else
	{
		m_pData=NULL;
	}
}

matrix::~matrix()
{
    if(m_pData!=NULL)
    {
        delete[] m_pData;
    }
}

matrix& matrix::operator=(const matrix& mat)
{
	if(this==&mat)
		return *this;
		
	delete[] m_pData;
	m_nRow=mat.m_nRow;
	m_nCol=mat.m_nCol;
	if(m_nRow*m_nCol>0)
	{
		m_pData=new MATDATA[m_nRow*m_nCol];
		memcpy(m_pData,mat.m_pData,sizeof(MATDATA)*m_nRow*m_nCol);
	}
	else
	{
		m_pData=NULL;
	}
	return *this;
}

UINT matrix::GetRowCount() const
{
    return m_nRow;
}

UINT matrix::GetColCount() const
{
    return m_nCol;
}

MATRET matrix::GetElement(UINT iRow,UINT iCol,MATDATA& rData) const
{
    if(iRow>=m_nRow)
    {
        return RET_INDEX_NOT_IN_ROW;
    }
    if(iCol>=m_nCol)
    {
        return RET_INDEX_NOT_IN_COL;
    }
    rData=*(m_pData+iRow*m_nCol+iCol);
    return RET_OK;
}

MATRET matrix::GetRowData(UINT iRow,MATDATA* pData,UINT nDataLen) const
{
	if(NULL==pData)
	{
		return RET_PARAM_POINT_NULL;
	}
    if(nDataLen!=m_nCol)
    {
        return RET_NOT_COL_MATCH;
    }
    if(iRow>=m_nRow)
    {
        return RET_INDEX_NOT_IN_ROW;
    }
    for(int j=0;j<m_nCol;j++)
    {
        *(pData+j)=*(m_pData+iRow*m_nCol+j);
    }
    return RET_OK;
}

MATRET matrix::GetColData(UINT iCol,MATDATA* pData,UINT nDataLen) const
{
	if(NULL==pData)
	{
		return RET_PARAM_POINT_NULL;
	}
    if(nDataLen!=m_nRow)
    {
        return RET_NOT_ROW_MATCH;
    }
    if(iCol>=m_nCol)
    {
        return RET_INDEX_NOT_IN_COL;
    }
    for(int i=0;i<m_nRow;i++)
    {
        *(pData+i)=*(m_pData+i*m_nCol+iCol);
    }
}


MATRET matrix::SetElement(UINT iRow,UINT iCol,MATDATA fData)
{
    if(iRow>=m_nRow)
    {
        return RET_INDEX_NOT_IN_ROW;
    }
    if(iCol>=m_nCol)
    {
        return RET_INDEX_NOT_IN_COL;
    }
    *(m_pData+iRow*m_nCol+iCol)=fData;
    return RET_OK;
}

MATRET matrix::SetRowData(UINT iRow,const MATDATA* pData,UINT nDataLen)
{
	if(NULL==pData)
	{
		return RET_PARAM_POINT_NULL;
	}
    if(iRow>=m_nRow)
    {
        return RET_INDEX_NOT_IN_ROW;
    }
    if(nDataLen!=m_nCol)
    {
        return RET_NOT_COL_MATCH;
    }
    for(int j=0;j<m_nCol;j++)
    {
        *(m_pData+iRow*m_nCol+j)=*(pData+j);
    }
    return RET_OK;
}

MATRET matrix::SetColData(UINT iCol,const MATDATA* pData,UINT nDataLen)
{
	if(NULL==pData)
	{
		return RET_PARAM_POINT_NULL;
	}
    if(iCol>=m_nCol)
    {
        return RET_INDEX_NOT_IN_COL;
    }
    if(nDataLen!=m_nRow)
    {
        return RET_NOT_ROW_MATCH;
    }
    for(int i=0;i<m_nRow;i++)
    {
        *(m_pData+i*m_nCol+iCol)=*(pData+i);
    }
    return RET_OK;
}

MATRET matrix::AppendRow(const MATDATA* pData,UINT nDataLen)
{
	if(NULL==pData)
	{
		return RET_PARAM_POINT_NULL;
	}
    if(nDataLen!=m_nCol)
    {
        return RET_NOT_COL_MATCH;
    }
    
    MATDATA* pTmp=new MATDATA[(m_nRow+1)*m_nCol];
    if(NULL==pTmp)
    {
    	return RET_NOT_ENOUGH_MEMERY;
    }
    memcpy(pTmp,m_pData,sizeof(MATDATA)*m_nRow*m_nCol);
    delete[] m_pData;
    m_pData=pTmp;

    for(int j=0;j<m_nCol;j++)
    {
        *(m_pData+m_nRow*m_nCol+j)=*(pData+j);
    }
    m_nRow+=1;
    return RET_OK;
}

MATRET matrix::AppendCol(const MATDATA* pData,UINT nDataLen)
{
	if(NULL==pData)
	{
		return RET_PARAM_POINT_NULL;
	}
    if(nDataLen!=m_nRow)
    {
        return RET_NOT_ROW_MATCH;
    }
    
    MATDATA* pTmp=new MATDATA[m_nRow*(m_nCol+1)];
    if(NULL==pTmp)
    {
    	return RET_NOT_ENOUGH_MEMERY;
    }
    MATDATA* pRowD=pTmp;
    MATDATA* pRowS=m_pData;
    for(int i=0;i<m_nRow;i++)
    {
    	memcpy(pRowD,pRowS,m_nCol*sizeof(MATDATA));
    	pRowD+=m_nCol+1;
    	pRowS+=m_nCol;
    }
    delete[] m_pData;
    m_pData=pTmp;
     
    for(int i=0;i<m_nRow;i++)
    {
        *(m_pData+i*m_nCol+m_nCol)=*(pData+i);
    }
    m_nCol+=1;
    return RET_OK;
}

MATRET matrix::GetUnitMatrix(UINT m,matrix** pRetmat)
{
	if(NULL==pRetmat)
	{
		return RET_PARAM_POINT_NULL;
	}
	if(NULL!=*pRetmat)
	{
		return RET_PARAM_POINT_NOT_NULL;
	}
    *pRetmat=new matrix(m,m);
    float* pval=(*pRetmat)->m_pData;
    for(int i=0;i<m;i++)
    {
        *pval=1.0;
        pval+=(m+1);
    }
    return RET_OK;
}

MATRET matrix::CombineMatrixH(const matrix& mat1,const matrix& mat2,matrix** pRetmat)
{
	if(NULL==pRetmat)
	{
		return RET_PARAM_POINT_NULL;
	}
	if(NULL!=*pRetmat)
	{
		return RET_PARAM_POINT_NOT_NULL;
	}

	if(mat1.m_nRow!=mat2.m_nRow)
	{
		return RET_NOT_ROW_MATCH;
	}
	*pRetmat=new matrix(mat1.m_nRow,mat1.m_nCol+mat2.m_nCol);
	if(NULL==*pRetmat)
	{
		return RET_NOT_ENOUGH_MEMERY;
	}

	MATDATA*pSrc1=mat1.m_pData;
	MATDATA*pSrc2=mat2.m_pData;
	MATDATA*pDst=(*pRetmat)->m_pData;
	
	for(int i=0;i<mat1.m_nRow;i++)
	{
		memcpy(pDst,pSrc1,sizeof(MATDATA)*mat1.m_nCol);
		pDst+=mat1.m_nCol;
		pSrc1+=mat1.m_nCol;
		memcpy(pDst,pSrc2,sizeof(MATDATA)*mat2.m_nCol);
		pDst+=mat2.m_nCol;
		pSrc2+=mat2.m_nCol;
	}
	return RET_OK;
}

MATRET matrix::CombineMatrixV(const matrix& mat1,const matrix& mat2,matrix** pRetmat)
{
	if(NULL==pRetmat)
	{
		return RET_PARAM_POINT_NULL;
	}
	if(NULL!=*pRetmat)
	{
		return RET_PARAM_POINT_NOT_NULL;
	}

	if(mat1.m_nCol!=mat2.m_nCol)
	{
		return RET_NOT_COL_MATCH;
	}

	*pRetmat=new matrix(mat1.m_nRow+mat2.m_nRow,mat1.m_nCol);
	if(NULL==*pRetmat)
	{
		return RET_NOT_ENOUGH_MEMERY;
	}
	
	MATDATA*pSrc=mat1.m_pData;
	MATDATA*pDst=(*pRetmat)->m_pData;
	
	memcpy(pDst,pSrc,sizeof(MATDATA)*mat1.m_nRow*mat1.m_nCol);
	pSrc=mat2.m_pData;
	pDst+=mat1.m_nRow*mat1.m_nCol;
	memcpy(pDst,pSrc,sizeof(MATDATA)*mat2.m_nRow*mat2.m_nCol);
	return RET_OK;
}

MATRET matrix::MatrixAdd(const matrix& mat1,const matrix& mat2,matrix** pRetmat)
{
	if(NULL==pRetmat)
	{
		return RET_PARAM_POINT_NULL;
	}
	if(NULL!=*pRetmat)
	{
		return RET_PARAM_POINT_NOT_NULL;
	}
	
	return RET_OK;
}

MATRET matrix::MatrixSub(const matrix& mat1,const matrix& mat2,matrix** pRetmat)
{
	if(NULL==pRetmat)
	{
		return RET_PARAM_POINT_NULL;
	}
	if(NULL!=*pRetmat)
	{
		return RET_PARAM_POINT_NOT_NULL;
	}
	return RET_OK;
}

MATRET matrix::MatrixMUl(const matrix& mat1,const matrix& mat2,matrix** pRetmat)
{
	if(NULL==pRetmat)
	{
		return RET_PARAM_POINT_NULL;
	}
	if(NULL!=*pRetmat)
	{
		return RET_PARAM_POINT_NOT_NULL;
	}
	return RET_OK;
}
