// -*- C++ -*-
#if !defined( TRANS_H__)
#define TRANS_H__

///////////////////////////////////////////////////////////////
//
//                 Simple & friendly
//             K a w a s a k i   R o b o t
//
//             Copyright (C) 2001 - 2008 By
//         System Technology Development Center,
//             Kawasaki Heavy Industries, LTD.
//
//    This software is furnished under a license and may be used
//    and copied only in accordance with the terms of such license
//    and with the inclusion of the above copyright notice.
//
///////////////////////////////////////////////////////////////

/*!
 * \file  trans.h
 * \brief 変換値クラス、各軸値クラスの定義
 * \author Akiyoshi Saiki
 */

#include <vector>
#include <iosfwd>

struct TMatrix;

namespace  KRcc
{
    class CVector;
/*!
 * \brief  Transformation value class
 *
 * XYZOAT format. (Eulerian coordinates.) 
 * 
 */
    class CTrans
    {
        friend class CArm;
        friend class CArmImpl;
        friend class CRobotImpl;
        friend class CInterpolationImp;

    private:
        // XYZOAT  XYZ:mm  OAT:degree
        std::vector<double> trans;

        double matrix_[4][3];
        TMatrix* matrix() { return reinterpret_cast<TMatrix*>( &matrix_[0][0] ); }
        const TMatrix* matrix() const { return reinterpret_cast<const TMatrix*>( &matrix_[0][0] ); }

    public:
        CTrans();
        ~CTrans();

        CTrans( const CTrans& );                           // Copy constructor
	explicit CTrans( size_t );                         // Constructor by size
        explicit CTrans( const std::vector<float> & );     // Constructor by floating format vector.
        explicit CTrans( const std::vector<double> & );    // Constructor by double format vector.

        // Set all parameter
        CTrans( double x, double y, double z, double o, double a, double t );

        // Set XYZ parameter. set OAT parameter zero.
        CTrans( double x, double y, double z );

        // Construct by charactor
        CTrans( const char*, char delim = ' ', int *num = NULL );


        CTrans& operator=( const CTrans& );         // assignment
        CTrans  operator-() const;		    // inverse


        const double&  operator[]( size_t i ) const;    // return transformation format value
        double&  operator[]( size_t i );                // return transformation format value
        double   X() const { return trans[0]; }		// return X value
        double   Y() const { return trans[1]; }		// return Y value
        double   Z() const { return trans[2]; }		// return Z value
        double   O() const { return trans[3]; }		// return O value
        double   A() const { return trans[4]; }		// return A value
        double   T() const { return trans[5]; }		// return T value

        CTrans  XYZ() const { return CTrans( X(), Y(), Z(), 0, 0, 0 ); } //!< XYZ
        CTrans  OAT() const { return CTrans( 0, 0, 0, O(), A(), T() ); } //!< OAT
    
        CTrans& set( const std::vector<float>& );	// set vector<float>
        CTrans& set( const std::vector<double>& );	// set vector<double>
        CTrans& set( double x, double y, double z );    // set XYZ

        // Set all parameter
        CTrans& set( double x, double y, double z, double o, double a, double t );
        // Set String value
        CTrans& set( const char*, char delim = ' ', int *num = NULL );
	// Copy data
        CTrans& set( const CTrans & );

        // set TMatrix
        CTrans &set( const TMatrix* );
        const TMatrix* const_matrix() const { return matrix(); }
        
        CTrans& update( bool=true ); 

        CTrans& clear();

        // Shift XYZ value ( -= CTrans(x,y,z))
        CTrans shift( double x, double y, double z ) const;

        CTrans &operator+=( const CTrans& );
        CTrans &operator-=( const CTrans& );

        const std::vector<double>& get() const { return trans; }
        size_t size() const { return trans.size(); }

        CTrans operator+( const CTrans& ) const;
        CTrans operator-( const CTrans& ) const;

        //! 変換値をストリームに文字列で吐き出す。OAT は degree
        friend std::ostream& operator << ( std::ostream& s, const CTrans& );

        static CTrans rx( double );		//!< Ｘ軸回りの回転(deg)
        static CTrans ry( double );		//!< Ｙ軸回りの回転(deg)
        static CTrans rz( double );		//!< Ｚ軸回りの回転(deg)


        //! フレーム生成：ＡＳの FRAM と同じ
        static CTrans frame( const CTrans&, const CTrans&, const CTrans&, const CTrans& );

        void setXForm( const double (&xform)[16] );
        void getXForm( double (&xform)[16] ) const;
#if defined(_MSC_VER) && _MSC_VER < 1400
        void setMatrix( double (&rtrans)[4][4] );
#else
        void setMatrix( const double (&rtrans)[4][4] );
#endif
        void getMatrix( double (&rtrans)[4][4] ) const;
        void setXyzXyz( const double (&xyzxyz)[6] );
        void getXyzXyz( double (&xyzxyz)[6] ) const;

        CTrans& unit();
    
        double getAxis( CVector &axis ) const;
        double dist( const CTrans& t ) const;

        CVector getVecX() const;
        CVector getVecY() const;
        CVector getVecZ() const;

        CTrans& setXYZ( double x, double y, double z );
        CTrans& setXYZ( const CVector &v );
        CTrans& setOAT( double o, double a, double t );
        CTrans& setOAT( const CVector &z_, const CVector &x_, bool& success);
        CTrans& setOAT( const CVector &z, double t );

        static CTrans rotVec( const CVector &axis, double angle );
        static CTrans ave( const CTrans &, const CTrans& );

        friend double diff( const CTrans &, const CTrans &, double r = 1000.0 );
    };

    double distance( const CTrans &, const CTrans & );


/*!
 * Joint format class
 *
 * RCC Library ではユーザに公開するクラスとして CJoint を使う。 \n
 * am_xx.cpp では ＡＳのソースを流用しているため、TJoint 構造体が
 * 使われているが、これはユーザには見せない。
 *
 * 軸値は内部では degree で保持\n
 * 文字列を引数に取るコンストラクタでは degree で指定する。\n
 * 直動外部軸の場合は mm 単位。
 */
    class CJoint
    {
        friend class CArm;
        friend class CArmImpl;
        friend class CRobotImpl;
    private:
        //! 各軸値を保持
        std::vector<double> angle;

    public:
        CJoint();
        ~CJoint();

        CJoint( const CJoint& );                  //!<  コピーコンストラクタ
	explicit CJoint( size_t );                         //!<  サイズを指定して生成
        explicit CJoint( const std::vector<float> & );     //!<  vector<float>から生成
        explicit CJoint( const std::vector<double> & );    //!<  vector<double>から生成

        //! 全部指定
        CJoint( double, double, double, double, double, double );
        //! 文字列（Degree）をスキャンして生成
        CJoint( const char*, char delim = ' ', int *num = NULL );

        //! 全部指定
        CJoint& set( double, double, double, double, double, double );
        CJoint& set( const std::vector<float>& );	//!<  vector<float>で設定
        CJoint& set( const std::vector<double>& );	//!<  vector<double>で設定

        //! 文字列（Degree）をスキャンして設定
        CJoint& set( const char*, char delim = ' ', int *num = NULL );

        CJoint& set( const CJoint & );

        CJoint& clear();		       //!< 全要素をゼロクリア

        //! 各軸の要素を返す(degree)
        const double&  operator[]( size_t ) const;
        double&  operator[]( size_t );
    
        //! 各軸値の要素を加算 
        CJoint operator+( const CJoint& ) const;
        //! 各軸値の要素を引算 
        CJoint operator-( const CJoint& ) const;

        CJoint& operator=( const CJoint & );             //!< 代入
        CJoint  operator-() const;                       //!< 全軸符号反転

        CJoint& operator+=( const CJoint & );
        CJoint& operator-=( const CJoint & );
        CJoint& operator*=( double );
        CJoint& operator/=( double );

        const std::vector<double>& get() const { return angle; }
        size_t size() const { return angle.size(); }

        //! 各軸値の内容をDegreeで ストリームに吐き出す
        friend std::ostream& operator << ( std::ostream& s, const CJoint& );

    };

    double diff( const CJoint&, const CJoint& );

    /*
     * \brief ベクタクラス
     */
    class CVector
    {
        double vec[3];
    public:
        CVector();
        CVector( double x, double y, double z );
        CVector( const std::vector<double> &v );
        CVector( const CVector& v );

        CVector& set( double x, double y, double z);
        CVector& set( const std::vector<double> &v );
        void get( double v[] );

        double x() const { return vec[0]; }
        double y() const { return vec[1]; }
        double z() const { return vec[2]; }
        const double& operator[]( size_t i ) const;
        double& operator[]( size_t i );
        
        CVector& init() { return set( 0, 0, 0 ); }

        double   length() const;
        CVector  unit() const ;
        CVector& normalize();
        CVector  ave( const CVector& ) const ;
        double   dot( const CVector&  ) const;
        CVector  prd( const CVector& v, bool& success, bool norm = true ) const;
        double   angle( const CVector& v ) const;

        CVector& operator=( const CVector& v );
        CVector  operator-() const;
	
        friend bool operator==( const CVector& v, const CVector& w );
        friend CVector operator+( const CVector& v, const CVector& w );
        friend CVector operator-( const CVector& v, const CVector& w );
        friend double operator*( const CVector& v, const CVector& w );
        friend CVector operator^( const CVector& v, const CVector& w );
        friend CVector operator*( const CVector& v, double m );
        friend CVector operator*( double m, const CVector& v );

        //friend CVector operator +( const CKTrans& t, const CVector& v );

        enum { ERR_NONE = 0, ERR_PRD = -1, ERR_VECUNIT = -2 };
    };


    /*
     * \brief  始点と終点を持つ直線
     */
    class CLine
    {
        CVector  start;    //!< 始点座標
        CVector  line;     //!< 始点→終点 ベクトル
    public:
        CLine() {}
        /*!
         * set() を呼んでメンバ変数を設定する
         * \param s 始点座標
         * \param e 終点座標
         */
        CLine( const CVector &s, const CVector &e )
        {
            set( s, e );
        }

        /*! 始点・終点を設定する \n
         *  同時に、始点→終点 ベクトルを計算する
         * \param s 始点座標
         * \param e 終点座標
         */
        void set( const CVector &s, const CVector &e )
        {
            start = s;
            line  = e - s;
        }

        /*! 線分の長さを計算する
         * \return 長さ
         */
        double length() const { return line.length(); }

        /*! 始点→終点のベクトル \n
         *  operator OverLoading で実装 \n
         * <pre>
         *     CLine  line( s, e )
         *     CVec   v = line;
         *     CVec   v = line.getVec();   // 同じ結果
         * </pre>
         *
         * \return 線分ベクトル
         */
        operator CVector() const { return line; }

        /*! 始点→終点のベクトル \
         * \return 線分ベクトル
         */
        CVector getVec() const { return line; }

        /*! 開始点から終了点に向かって、比率指定により定義される
         * 位置の座標を取得する。 \n
         * \param ratio  比率 :  0.0 の時 始点、1.0 の時 終点を返す
         */
        CVector getByRatio( double ratio ) const
        {
            return  start + line * ratio;
        }
    };
}

#endif  /* TRANS_H__ */
