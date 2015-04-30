/*
 * 
 * Ref:
 *  http://en.cppreference.com/w/cpp/locale/numpunct/thousands_sep
 */

#ifndef CS540_OSTREAM_WRAPPER_HPP
#define CS540_OSTREAM_WRAPPER_HPP

#include<iostream>
#include<locale>

#define DEBUG_STM(fmt) \
        std::cout<<__FILE__<<":"<<__FUNCTION__<<":"<<__LINE__<<": "<<fmt<<std::endl

namespace cs540 {
          
  struct sep_struct {char m_c;};
    
  class OstreamWrapper{
    private:
      std::ostream &m_outStream;
    public:
    //OstreamWrapper(){}
    OstreamWrapper(std::ostream& os) : m_outStream(os){
      setDefaultLocale();
    }
    ~OstreamWrapper(){}
    
    void setDefaultLocale(){
      this->m_outStream.imbue(std::locale());
    }
    
    void setSep(char c){
      struct separator_helper : std::numpunct<char> {
        separator_helper(char c) : m_c(c){}
        char m_c;
        char do_thousands_sep()   const { return m_c; }
        std::string do_grouping() const { return "\3"; } 
      };
      this->m_outStream.imbue(std::locale(this->m_outStream.getloc(), new separator_helper(c)));
    }
    
    friend OstreamWrapper& operator<<(OstreamWrapper& os, const int& i){
      os.m_outStream<<i;
      return os;
    }
    
    friend OstreamWrapper& operator<<(OstreamWrapper& os, const char *c){
      os.m_outStream<<c;
      return os;
    }
    
    friend OstreamWrapper& operator<<(OstreamWrapper& os, std::ostream &(*f)(std::ostream &)){
      os.m_outStream<<f;
      return os;
    }
    
    friend OstreamWrapper& operator<<(OstreamWrapper& os, OstreamWrapper &(*f)(OstreamWrapper &)){
      return f(os);
    }
    
    friend OstreamWrapper& operator<<(OstreamWrapper& os, sep_struct s){
      os.setSep(s.m_c);
      return os;
    }
    
  };
  
  OstreamWrapper& nosep(OstreamWrapper& os){
    os.setDefaultLocale();
    return os;
  }

  inline sep_struct sep(char c){
    sep_struct s;
    s.m_c = c;
    return s;
  }
  

} // namespace cs540

#endif
