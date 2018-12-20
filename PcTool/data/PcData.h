#pragma once

////////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <sstream>
////////////////////////////////////////////////////////////////////////////////

class PcCfg
{
public:
	PcCfg() throw()
	{
	}
	PcCfg(PcCfg&& src) : m_vecGray(std::move(src.m_vecGray)),
						m_vecR(std::move(src.m_vecR)),
						m_vecG(std::move(src.m_vecG)),
						m_vecB(std::move(src.m_vecB))
	{
	}
	~PcCfg() throw()
	{
	}

	PcCfg& operator=(PcCfg&& src) throw()
	{
		m_vecGray = std::move(src.m_vecGray);
		m_vecR = std::move(src.m_vecR);
		m_vecG = std::move(src.m_vecG);
		m_vecB = std::move(src.m_vecB);
		return *this;
	}

	size_t GetCount() const throw()
	{
		return m_vecGray.size();
	}
	int GetGrayAt(size_t index) const throw()
	{
		assert( index < GetCount() );
		return m_vecGray[index];
	}
	void GetRgbAt(size_t index, int& r, int& g, int& b) const throw()
	{
		assert( index < GetCount() );
		r = m_vecR[index];
		g = m_vecG[index];
		b = m_vecB[index];
	}
	void SetGrayAt(size_t index, int gray) throw()
	{
		assert( index < GetCount() );
		m_vecGray[index] = gray;
	}
	void SetRAt(size_t index, int r) throw()
	{
		assert( index < GetCount() );
		m_vecR[index] = r;
	}
	void SetGAt(size_t index, int g) throw()
	{
		assert( index < GetCount() );
		m_vecG[index] = g;
	}
	void SetBAt(size_t index, int b) throw()
	{
		assert( index < GetCount() );
		m_vecB[index] = b;
	}

	bool Load(LPCTSTR szFile)
	{
		clear();

		std::ifstream fin(szFile, std::ios::in);
		if( !fin.is_open() )
			return false;
		std::string strLine;
		while( std::getline(fin, strLine) ) {
			if( strLine.length() != 0 ) {
				std::stringstream st(strLine, std::ios::in);
				int v;
				st >> v;
				m_vecGray.push_back(v);
				st >> v;
				m_vecR.push_back(v);
				st >> v;
				m_vecG.push_back(v);
				st >> v;
				m_vecB.push_back(v);
			}
		}
		fin.close();
		if( m_vecGray.size() == 0 )
			return false;
		//check
		for( size_t i = 0; i < m_vecGray.size(); i ++ ) {
			if( m_vecGray[i] < 0 || m_vecGray[i] > 255 )
				return false;
			if( m_vecR[i] < 0 || m_vecR[i] > 255 )
				return false;
			if( m_vecG[i] < 0 || m_vecG[i] > 255 )
				return false;
			if( m_vecB[i] < 0 || m_vecB[i] > 255 )
				return false;
			if( i != m_vecGray.size() - 1 ) {
				if( m_vecGray[i] >= m_vecGray[i + 1] )
					return false;
			}
		}
		return true;
	}
	bool Save(LPCTSTR szFile)
	{
		std::ofstream fout(szFile, std::ios::out | std::ios::trunc);
		if( !fout.is_open() )
			return false;
		for( size_t i = 0; i < m_vecGray.size(); i ++ ) {
			fout << m_vecGray[i];
			fout << " ";
			fout << m_vecR[i];
			fout << " ";
			fout << m_vecG[i];
			fout << " ";
			fout << m_vecB[i];
			fout << std::endl;
		}
		fout.close();
		return true;
	}

private:
	void clear() throw()
	{
		m_vecGray.clear();
		m_vecR.clear();
		m_vecG.clear();
		m_vecB.clear();
	}

private:
	std::vector<int> m_vecGray;
	std::vector<int> m_vecR;
	std::vector<int> m_vecG;
	std::vector<int> m_vecB;

private:
	PcCfg(const PcCfg&) throw();
	PcCfg& operator=(const PcCfg&) throw();
};

////////////////////////////////////////////////////////////////////////////////
