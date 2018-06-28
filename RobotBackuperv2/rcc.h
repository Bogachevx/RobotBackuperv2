// -*- C++ -*-
#if !defined( RCC_H__)
#define RCC_H__

///////////////////////////////////////////////////////////////
//
//                 Simple & friendly
//             K a w a s a k i   R o b o t
//
//    Copyright (C) 2001,2002,2003,2004,2005,2006 By
//         System Technology Development Center,
//             Kawasaki Heavy Industries, LTD.
//
//    This software is furnished under a license and may be used
//    and copied only in accordance with the terms of such license
//    and with the inclusion of the above copyright notice.
//
///////////////////////////////////////////////////////////////

/*!
 \file  rcc.h
 \brief  Kawasaki `Robot Control Class` Library
 \author Akiyoshi Saiki
 \version 2.0
*/

#include <exception>
#include <string>
#include "trans.h"

namespace KRcc
{

/*!
 * \brief �A�[���ɑ΂���C���^�[�t�F�[�X��񋟂���
 */
class CArm
{
    friend class CRobot;
    friend class CRobotImpl;
    CArm& operator=( const CArm& );	//!< ����֎~

#ifndef DOXYGEN_ONLY
    // Handle-Body Idiom
    struct { void* padding[2]; } p_body;
#else
    class CArmImpl *p_body;
#endif

 public:
    //! �R���X�g���N�^
    CArm( const char * arm_type );
    CArm( const CArm& r );        //!< �R�s�[

    //! �f�X�g���N�^
    ~CArm();

    //! �A�[������
    const char* name() const;

    //! �c�[���ݒ�
    void tool( const CTrans& t );
    //! �x�[�X���W�ݒ�
    void base( const CTrans& b );
    //! �c�[���ϊ��l�擾
    const CTrans &tool(void) const;
    //! �x�[�X���W�l�擾
    const CTrans &base(void) const;
    
    int  error() const;		//! ���t�ϊ��̃G���[�R�[�h
    bool enable_throw( bool );	//! �t�ϊ����̗�O�� throw ����^���Ȃ��̑I��

    //! ���ϊ�
    CTrans point( const CJoint& ) const;

    //! �t�ϊ��F�Q�Ǝp���ƌ`�Ԃ��w��F
    CJoint point( const CTrans&, const CJoint &ref, int conf ) const;

    //! �t�ϊ��F�Q�Ǝp�����w��F�`�Ԃ� ref ����v�Z
    CJoint point( const CTrans& tr, const CJoint &ref ) const;

    //! �t�ϊ��F���ϕ����
    CJoint hybrid( const CTrans& xyz, const CJoint &jt456,
		   const CJoint &ref ) const;

    //! �e���l����`�Ԃ𔻒�
    int config( const CJoint &jt ) const;

    size_t  num_jt() const;                   //!< �O�������܂܂Ȃ�����
};

/*!
 * \brief  �ʐM�Ɋւ���C���^�[�t�F�[�X��񋟂���
 */
class CCommu
{
    friend class CRobot;
    CCommu& operator=( const CCommu& );	//!< ����֎~

#ifndef DOXYGEN_ONLY
    // Handle-Body Idiom
    struct { void* padding[2]; } p_body;
#else
    class CCommuImpl *p_body;
#endif

 public:
    CCommu( const char *cmmu_port = NULL );
    CCommu( const CCommu & );
    virtual ~CCommu();

    //! �ʐM�|�[�g����
    const char* name() const;

    //! �R���g���[���ւ̐ڑ������F1XA,TCP,Serial
    bool connect( const char *commu_type );
    bool disconnect();

    //! ���j�^�R�}���h�����s
    int command( const char *cmd,  char *buf, size_t sz, int tmo = 500 );
    //! ���j�^�R�}���h�����s
    int command( const char *cmd, std::string &resp, int tmo = 500 /*msec*/ );
    //! ���j�^�R�}���h�����s
    int command( const char *cmd, int tmo = 500 /*msec*/ );

    //! �`�r�v���O�������R���g���[����Load
    int load( const char *fname, const char *qual = NULL );

    //! �`�r�v���O�������z�X�g��Save
    int save( const char *fname,
              const char *prog = NULL, const char *qual = NULL );

    // save/load �� callback
    virtual void callbackProgress( long cur, long total );
    virtual bool callbackInquiry( const std::string &as_msg, std::string &resp );
    const char *getLoadSaveMsg() const;

    //! �ʐM���O�J�n
    bool startLog( const char *log_fname  );
    //! �ʐM���O�I��
    bool stopLog();

    int send( const char *p, unsigned sz );

    bool is_connected();
    void setTimeoutValue( unsigned int msec );
};


/*!
 * \brief CArm �� CCommu ���܂�
 *
 */
class CRobot
{
#ifndef DOXYGEN_ONLY
    // Handle-Body Idiom
    struct { void* padding[2]; } p_body;
#else
    class CRobotImpl *p_body;
#endif

    CRobot& operator=( const CRobot& );	//!< ����֎~

public:
    CRobot( const char * arm_, const char *comm_ = NULL);
    CRobot( const CRobot& r_ );   //!< �R�s�[
    ~CRobot();

    CCommu &com();

    //! �A�[������
    const char* name() const;

    //! ���t�ϊ��̃G���[�R�[�h
    int  error() const;
    //! �t�ϊ����̗�O�� throw ����^���Ȃ��̑I��
    bool enable_throw( bool b );

    //! �c�[���ݒ�
    void tool( const CTrans& t );
    //! �x�[�X���W�ݒ�
    void base( const CTrans& b );
    //! �c�[���ϊ��l�擾
    const CTrans &tool(void) const;
    //! �x�[�X���W�l�擾
    const CTrans &base(void) const;

    //! �e���l����`�Ԃ𔻒�
    int config( const CJoint &jt ) const;
    //! ���ݒl�̌`�Ԃ��擾
    int config() const;

    //! ���ϊ�
    CTrans point( const CJoint& ) const;

    //! �t�ϊ��F�Q�Ǝp���ƌ`�Ԃ��w��F
    CJoint point( const CTrans&, const CJoint &ref, int conf ) const;

    //! �t�ϊ��F�Q�Ǝp�����w��F�`�Ԃ� ref ����v�Z
    CJoint point( const CTrans& tr, const CJoint &ref ) const;
    //! �t�ϊ��F�`�Ԃ��w��F�Q�Ǝp���͌��ݒl
    CJoint point( const CTrans& tr, int conf ) const;
    //! �t�ϊ��F�Q�Ǝp���ƌ`�Ԃ͌��ݒl
    CJoint point( const CTrans& tr ) const;

    //! �t�ϊ��F���ϕ����
    CJoint hybrid( const CTrans& xyz, const CJoint &jt456,
		   const CJoint &ref ) const;
    //! �t�ϊ��F���ϕ����
    CJoint hybrid( const CTrans& xyz, const CJoint &jt456 ) const;

    // op. Instruction
    void lMove( const CTrans &tr );
    void lMove( const CJoint &jt );
    void jMove( const CTrans &tr );
    void jMove( const CJoint &jt );
    void xMove( const CTrans &tr, int sig );
    void xMove( const CJoint &jt, int sig );
    void jAppro( const CTrans&, double );
    void jAppro( const CJoint&, double );
    void lAppro( const CTrans&, double );
    void lAppro( const CJoint&, double );
    void jDepart( double );
    void lDepart( double );

    void c1Move( const CTrans & );
    void c1Move( const CJoint & );
    void c2Move( const CTrans & );
    void c2Move( const CJoint & );

    void call( const char * );

    void mBreak( bool sync=false );
    void accuracy( double n, bool always=0 );
    enum { PERCENT, MMPS, SEC };
    void speed( double n, int unit=PERCENT, bool always=false );
    void accel( double n, bool always=0 );
    void decel( double n, bool always=0 );
    
    void here( CTrans &tr );   //!< ���ݒl��ϊ��l�Ŏ擾
    void here( CJoint &tr );   //!< ���ݒl���e���l�Ŏ擾

    CJoint ulim() const;
    CJoint llim() const;
    CJoint jointSpeed() const;

    void ulim( const CJoint& );
    void llim( const CJoint& );
    void jointSpeed( const CJoint& );

    void add( const class CExtLinAxis& );	//!< �O�����i�������j�̐ݒ�
    void add( const class CExtRotAxis& );	//!< �O�����i��]���j�̐ݒ�

    size_t  num_jt() const;        		//!< �O�������܂ޑS����

    //! ���z�R���g���[���Ɏ��@�̐�p�o�͐M�����}�b�s���O����
    int defsig( const char *sig_name, int no );
};

/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////

    //! �t�ϊ��F�G���[�R�[�h
enum { OutOfLoUsrlim = -852,  OutOfHiUsrlim = -853,  OutOfRange = -857 };
    //! �`��
enum { Righty=0, Above=0, Dwrist=0, Lefty=0x01, Below=0x02, Uwrist=0x04 };

    //! �`�Ԃ̔���
inline bool isLefty( int conf )  { return ( conf & Lefty  ) != 0; }
inline bool isBelow( int conf )  { return ( conf & Below  ) != 0; }
inline bool isUWrist( int conf ) { return ( conf & Uwrist )!= 0;  }
inline bool isRighty( int conf ) { return !isLefty( conf );  }
inline bool isAbove( int conf )  { return !isBelow( conf );  }
inline bool isDWrist( int conf ) { return !isUWrist( conf ); }


//! RCC �S�̂̃f�o�b�O�t���O
extern long dbgFlag;
//! �Ή��A�[�����̃��X�g "...\0...\0...\0\0"
extern const char* rccArmList;

/////////////////////////////////////////

/////////////////////////////////////////

/*!
 * \brief  �O���� �ݒ�  ���ۃN���X
 */
class CExtAxis
{
    friend class CRobotImpl;
protected:
    double llim, ulim;
    double max_spd;

    // XYZ: �����N����
    // OAT: ���s���͈ړ������A��]���͉�]������
    CTrans matrix;

public:
    CExtAxis( double ulim, double llim, double max_spd );
    CExtAxis( const CExtAxis &);
    virtual ~CExtAxis();
    virtual CTrans vec( double val ) const = 0;
    CExtAxis &operator =( const CExtAxis & );
};

/*!
 * \brief  ������
 */
class CExtLinAxis : public CExtAxis
{
public:
    CExtLinAxis( double ulim, double llim, double max_spd )
      : CExtAxis( ulim, llim, max_spd ) {}
    ~CExtLinAxis();
    virtual CTrans vec( double val ) const;    // �I�t�Z�b�g�{���s����
};


/*!
 * \brief  ��]��
 */
class CExtRotAxis : public CExtAxis
{
public:
    CExtRotAxis( double ulim, double llim, double max_spd )
      : CExtAxis( ulim, llim, max_spd ) {}
    ~CExtRotAxis();
    virtual CTrans vec( double val ) const;   // �I�t�Z�b�g�{��]�x�N�g��
};

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

/*!
 * \brief  �`�r�ϐ����\����͊�
 *
 * ������ŗ^����ꂽ�ϊ��l���Z������������
 */
class CParser
{
    CParser( const CParser & );		//!< �R�s�[�֎~
    CParser& operator =( const CParser & );   //!< �R�s�[�֎~

    friend class CParserImpl;
    class CParserImpl *body;
    class CAsVar *as_var;

protected:
    //!����������i���[�U�Ē�`�\�j
    virtual const void* var_assign( int type, const char *, const void *p );
    //!�ϐ��Q�Ə����i���[�U�Ē�`�\�j
    virtual const void* var_ref( int type, const char * );

public:
    enum TMotionOpe {
        OP_Unkown = 0,
        OP_JMOVE, OP_LMOVE, OP_HMOVE, OP_C1MOVE, OP_C2MOVE,
        OP_JAPPRO, OP_LAPPRO,
        OP_JDEPART, OP_LDEPART,
        OP_JOINT, OP_LINEAR,
        OP_DRIVE,
        OP_DRAW, OP_TDRAW,
        OP_JWS, OP_LWS, OP_LWC, OP_LWE, OP_C1WC, OP_C2WC, OP_C2WE
    };
    enum  { Unkown=0, Trans=0x01, Joint=0x02, Real=0x04,  Motion=0x100 };
    struct answer
    {
        int    type;
        CTrans trans;
        CJoint joint;
        float  real;
        int    ope;       // TMotionOpe
    } answer;

    CParser();
    CParser( CRobot &robot );
    virtual ~CParser();

    void clear();

    int  parse( const char * );
    const char *getLastError() const;

    const CTrans& trans() const;    //!< �ϊ��l��Ԃ�
    const CJoint& joint() const;    //!< �e���l��Ԃ�
    float real() const;             //!< �����l��Ԃ�

    friend std::istream& operator >>( std::istream&, CParser &);
};

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

/*
 * \brief ��Ԍv�Z�p base �N���X
 *
 * CIntJoint/CIntLinear/CIntCircular/CIntHybrid �͂��̃N���X�̔h��
 */
class CInterpolation
{
protected:
    class CInterpolationImp *body;    //!< ��Ԍv�Z�̎���
    CInterpolation();
public:
    virtual ~CInterpolation();

    CInterpolation &operator()( double s );    //!< ��ԌW���̐ݒ�

    operator CJoint() const;    //!< �e���l��Ԃ�
    operator CTrans() const;    //!< �ϊ��l��Ԃ�
    double distance() const;
};

/*!
 * \brief �e�����
 */
class CIntJoint : public CInterpolation
{
    CIntJoint( const CIntJoint& );		  //!< �R�s�[�֎~
    CIntJoint &operator =( const CIntJoint& );    //!< ����֎~
public:
    CIntJoint( const CJoint&, const CJoint& );
    CIntJoint( const CRobot&, const CJoint&, const CJoint& );
    virtual ~CIntJoint();
};

/*!
 * \brief �������
 */
class CIntLinear : public CInterpolation
{
    CIntLinear( const CIntLinear& );              //!< �R�s�[�֎~
    CIntLinear &operator =( const CIntLinear& );  //!< ����֎~
public:
    CIntLinear( const CTrans&, const CTrans& );
    CIntLinear( const CRobot&, const CJoint&, const CJoint& );
    virtual ~CIntLinear();
};

/*!
 * \brief �~�ʕ��
 */
class CIntCircular : public CInterpolation
{
    CIntCircular( const CIntCircular& );             //!< �R�s�[�֎~
    CIntCircular &operator =( const CIntCircular& ); //!< ����֎~
public:
    CIntCircular( const CTrans&, const CTrans&, const CTrans&,
                  bool last_half = false );
    CIntCircular( const CRobot&, const CJoint&, const CJoint&, const CJoint&, 
                  bool last_half = false );
    virtual ~CIntCircular();
};

/*!
 * \brief ���ϕ����
 */
class CIntHybrid : public CInterpolation
{
    CIntHybrid( const CIntHybrid& );		    //!< �R�s�[�֎~
    CIntHybrid &operator =( const CIntHybrid& );    //!< ����֎~
public:
    CIntHybrid( const CRobot&, const CJoint&, const CJoint& );
    virtual ~CIntHybrid();
};


/*!
 * \brief �~�ʎ��ϕ����
 */
class CIntHybridCircular : public CInterpolation
{
    CIntHybridCircular( const CIntHybridCircular& );		    //!< �R�s�[�֎~
    CIntHybridCircular &operator =( const CIntHybridCircular& );    //!< ����֎~
public:
    CIntHybridCircular( const CRobot&, const CJoint&, const CJoint&, const CJoint&,
                        bool last_half = false );
    virtual ~CIntHybridCircular();
};

/////////////////////////////////////////////////////////////


/*!
 * \brief RCC ��O����
 */
class rcc_exception : public std::exception
{
#if defined(_MSC_VER)
public:
    rcc_exception( const char *s = "rcc exception" ) throw ()
		: std::exception( s ) {}
#else
    const char *ex_str;
public:
    rcc_exception( const char *s = "rcc exception" ) throw ()
		: ex_str(s) {}
    const char* what()  const throw() { return ex_str; }
#endif
};

/////////////////////////////////////////


} // namespace KRcc

#endif /* RCC_H */
