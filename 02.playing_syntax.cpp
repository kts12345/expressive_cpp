#include <string>
#include <boost/proto/proto.hpp>
 
struct map_ {};
boost::proto::terminal<map_>::type map = {};
 
template< class Expr >
void format( std::string fmt, Expr const & expr )
{}
 
int main()
{
    auto pxp_01 =  map("place", "heaven and earth")
                      ("thing", "philosophy");
                     
    auto pxp_02 =  map["place"]("heaven and earth")
                      ["thing"]("philosophy");
    
    auto pxp_03 =  map["place"] = "heaven and earth" +
                   map["thing"] = "philosophy";
    
    auto pxp_04 = (map["place"] = "heaven and earth",
                   map["thing"] = "philosophy");
                            
    // OK, valid C++ expressions:
    format( "There are...", pxp_01 ); 
    format( "There are...", pxp_02 ); 
    format( "There are...", pxp_03 ); 
    format( "There are...", pxp_04 );
        
    boost::proto::display_expr(pxp_01);
    boost::proto::display_expr(pxp_02);
    boost::proto::display_expr(pxp_03);
    boost::proto::display_expr(pxp_04);
}

/*
clang++ -std=c++1y -O2 -Wall -pedantic main.cpp && ./a.out

function(
    function(
        terminal(4map_)
      , terminal(place)
      , terminal(heaven and earth)
    )
  , terminal(thing)
  , terminal(philosophy)
)
function(
    subscript(
        function(
            subscript(
                terminal(4map_)
              , terminal(place)
            )
          , terminal(heaven and earth)
        )
      , terminal(thing)
    )
  , terminal(philosophy)
)
assign(
    subscript(
        terminal(4map_)
      , terminal(place)
    )
  , assign(
        plus(
            terminal(heaven and earth)
          , subscript(
                terminal(4map_)
              , terminal(thing)
            )
        )
      , terminal(philosophy)
    )
)
comma(
    assign(
        subscript(
            terminal(4map_)
          , terminal(place)
        )
      , terminal(heaven and earth)
    )
  , assign(
        subscript(
            terminal(4map_)
          , terminal(thing)
        )
      , terminal(philosophy)
    )
)
*/
