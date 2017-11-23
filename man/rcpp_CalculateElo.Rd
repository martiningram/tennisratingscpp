\name{CalculateElo}
\alias{CalculateElo}
\docType{package}
\title{
Calculate the win expectation from player Elo ratings with match-based learning rate
}
\description{
  Calculates a player's win expectation given their skill as well as their
  opponent's and both players' career matches.
}
\arguments{
  \item{winner_names}{String vector of names of match winners}
  \item{loser_names}{String vector of names of match losers}
  \item{winner_match}{Numeric vector of career matches played by match winner}
  \item{loser_match}{Numeric vector of career matches played by match loser}
  \item{slam}{Numeric vector to incorporate slam multiplier (set equal to 1 to have not effect on rate)}
}
\value{
  The probability that P1 wins.
}
\usage{
  CalculateElo(winner_names, loser_names, winner_match, loser_match, slam_factor)
}
