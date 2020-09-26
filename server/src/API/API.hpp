//
// Created by Jean-Gaël Choppe on 26/09/2020.
//

#ifndef BABEL_API_HPP
#define BABEL_API_HPP

namespace Server {
    class API {
    public:
        API(/* Router */);

        bool handler();

    private:
        Router _Router;
    };
}


#endif //BABEL_API_HPP
