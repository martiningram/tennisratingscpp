\name{ServeReturnEloStaticK}
\alias{ServeReturnEloStaticK}
\docType{package}
\title{
Calculate serve and return Elo with a fixed k-factor
}
\description{
  This function calculates serve and return Elos for a static k factor.
}
\value{
  A list containing fields, "server_elos" and "returner_elos" with the player
  elo ratings for each point.
}
\usage{
ServeReturnEloStaticK(server_names, returner_names, server_won, k,
                      return_starting_elo = 1410)
}
\examples{
\dontrun{
ServeReturnEloStaticK(c('Roger Federer', 'Roger Federer'),
                      c('Rafael Nadal', 'Rafael Nadal'),
                      c(TRUE, TRUE),
                      1.,
                      1405.)
}
}
