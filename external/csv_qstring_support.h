#include <QString>

namespace io {
	namespace detail {
		template<class overflow_policy>
		void parse(char *col, QString &x){
				x = col;
		}
	}
}
