\name{CalculateGlickoWinExpectation}
\alias{CalculateGlickoWinExpectation}
\docType{package}
\title{
Calculate the win expectation given players' Glicko ratings
}
\description{
  Calculates a player's win expectation given their skill as well as their
  opponent's.
}
\arguments{
  \item{mu}{Player 1's mean skill.}
  \item{sigma_sq}{Player 1's skill variance.}
  \item{mu_j}{Player 2's mean skill.}
  \item{sigma_sq_j}{Player 2's skill variance.}
}
\value{
  The probability that P1 wins.
}
\usage{
  CalculateGlickoWinExpectation(mu, sigma_sq, mu_j, sigma_sq_j)
}
\references{
  The Glicko paper: \url{http://www.glicko.net/research/glicko.pdf}
}
\examples{
\dontrun{
  CalculateGlickoWinExpectation(mu = 1510.,
                                sigma_sq = 1000.,
                                mu_j = 1600.,
                                sigma_sq_j = 900.)
}
}
