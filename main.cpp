#include "SpotifyClient.hpp"

constexpr char dev_token[] = "BQCeKLInrd4FCQgv3wTCQ-xRN6vmEWtfdGyz8uCpFcKE3zLQVO2hv0R1RcGIzfL_83XvqvTaM9V_KHyLloyuoxl9CZJzvKTHIAu7jS70P8LyqehTOTqSvdalGfqlIy4R4K1J5lYlphCxj0-ZxjUZQPmE";


int main(void)
{
    spotify::SpotifyClient client{dev_token};    
    client.searchTrack("Ela Partiu");
}