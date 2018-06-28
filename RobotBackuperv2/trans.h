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
 * \brief �ϊ��l�N���X�A�e���l�N���X�̒�`
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

        //! �ϊ��l���X�g���[���ɕ�����œf���o���BOAT �� degree
        friend std::ostream& operator << ( std::ostream& s, const CTrans& );

        static CTrans rx( double );		//!< �w�����̉�](deg)
        static CTrans ry( double );		//!< �x�����̉�](deg)
        static CTrans rz( double );		//!< �y�����̉�](deg)


        //! �t���[�������F�`�r�� FRAM �Ɠ���
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
 * RCC Library �ł̓��[�U�Ɍ��J����N���X�Ƃ��� CJoint ���g���B \n
 * am_xx.cpp �ł� �`�r�̃\�[�X�𗬗p���Ă��邽�߁ATJoint �\���̂�
 * �g���Ă��邪�A����̓��[�U�ɂ͌����Ȃ��B
 *
 * ���l�͓����ł� degree �ŕێ�\n
 * ������������Ɏ��R���X�g���N�^�ł� degree �Ŏw�肷��B\n
 * �����O�����̏ꍇ�� mm �P�ʁB
 */
    class CJoint
    {
        friend class CArm;
        friend class CArmImpl;
        friend class CRobotImpl;
    private:
        //! �e���l��ێ�
        std::vector<double> angle;

    public:
        CJoint();
        ~CJoint();

        CJoint( const CJoint& );                  //!<  �R�s�[�R���X�g���N�^
	explicit CJoint( size_t );                         //!<  �T�C�Y���w�肵�Đ���
        explicit CJoint( const std::vector<float> & );     //!<  vector<float>���琶��
        explicit CJoint( const std::vector<double> & );    //!<  vector<double>���琶��

        //! �S���w��
        CJoint( double, double, double, double, double, double );
        //! ������iDegree�j���X�L�������Đ���
        CJoint( const char*, char delim = ' ', int *num = NULL );

        //! �S���w��
        CJoint& set( double, double, double, double, double, double );
        CJoint& set( const std::vector<float>& );	//!<  vector<float>�Őݒ�
        CJoint& set( const std::vector<double>& );	//!<  vector<double>�Őݒ�

        //! ������iDegree�j���X�L�������Đݒ�
        CJoint& set( const char*, char delim = ' ', int *num = NULL );

        CJoint& set( const CJoint & );

        CJoint& clear();		       //!< �S�v�f���[���N���A

        //! �e���̗v�f��Ԃ�(degree)
        const double&  operator[]( size_t ) const;
        double&  operator[]( size_t );
    
        //! �e���l�̗v�f�����Z 
        CJoint operator+( const CJoint& ) const;
        //! �e���l�̗v�f�����Z 
        CJoint operator-( const CJoint& ) const;

        CJoint& operator=( const CJoint & );             //!< ���
        CJoint  operator-() const;                       //!< �S���������]

        CJoint& operator+=( const CJoint & );
        CJoint& operator-=( const CJoint & );
        CJoint& operator*=( double );
        CJoint& operator/=( double );

        const std::vector<double>& get() const { return angle; }
        size_t size() const { return angle.size(); }

        //! �e���l�̓��e��Degree�� �X�g���[���ɓf���o��
        friend std::ostream& operator << ( std::ostream& s, const CJoint& );

    };

    double diff( const CJoint&, const CJoint& );

    /*
     * \brief �x�N�^�N���X
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
     * \brief  �n�_�ƏI�_��������
     */
    class CLine
    {
        CVector  start;    //!< �n�_���W
        CVector  line;     //!< �n�_���I�_ �x�N�g��
    public:
        CLine() {}
        /*!
         * set() ���Ă�Ń����o�ϐ���ݒ肷��
         * \param s �n�_���W
         * \param e �I�_���W
         */
        CLine( const CVector &s, const CVector &e )
        {
            set( s, e );
        }

        /*! �n�_�E�I�_��ݒ肷�� \n
         *  �����ɁA�n�_���I�_ �x�N�g�����v�Z����
         * \param s �n�_���W
         * \param e �I�_���W
         */
        void set( const CVector &s, const CVector &e )
        {
            start = s;
            line  = e - s;
        }

        /*! �����̒������v�Z����
         * \return ����
         */
        double length() const { return line.length(); }

        /*! �n�_���I�_�̃x�N�g�� \n
         *  operator OverLoading �Ŏ��� \n
         * <pre>
         *     CLine  line( s, e )
         *     CVec   v = line;
         *     CVec   v = line.getVec();   // ��������
         * </pre>
         *
         * \return �����x�N�g��
         */
        operator CVector() const { return line; }

        /*! �n�_���I�_�̃x�N�g�� \
         * \return �����x�N�g��
         */
        CVector getVec() const { return line; }

        /*! �J�n�_����I���_�Ɍ������āA�䗦�w��ɂ���`�����
         * �ʒu�̍��W���擾����B \n
         * \param ratio  �䗦 :  0.0 �̎� �n�_�A1.0 �̎� �I�_��Ԃ�
         */
        CVector getByRatio( double ratio ) const
        {
            return  start + line * ratio;
        }
    };
}

#endif  /* TRANS_H__ */
