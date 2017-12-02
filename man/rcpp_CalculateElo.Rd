\name{CalculateElo}
\alias{CalculateElo}
\docType{package}
\title{
Calculate player Elo ratings with match-based learning rate
}
\description{
  Calculates a player's win expectation given their skill as well as their
  opponent's and both players' career matches. It uses 538's formula for k.
}
\arguments{
  \item{winner_names}{String vector of names of match winners}
  \item{loser_names}{String vector of names of match losers}
  \item{winner_match}{Numeric vector of career matches played by match winner}
  \item{loser_match}{Numeric vector of career matches played by match loser}
  \item{slam_factor}{Numeric vector to incorporate slam multiplier. This
    pre-multiplies the k factor; set equal to 1 to have no effect on rate.}
}
\value{
  A list containing fields "winner_elo" and "loser_elo" containing the players'
  Elo ratings before the match update.
}
\usage{
  CalculateElo(winner_names, loser_names, winner_match, loser_match, slam_factor)
}
