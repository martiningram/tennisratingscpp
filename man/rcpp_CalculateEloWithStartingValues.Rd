\name{CalculateEloWithStartingValues}
\alias{CalculateEloWithStartingValues}
\docType{package}
\title{
Calculate player Elo ratings with match-based learning rate and known starting
values.
}
\description{
  Calculates a player's win expectation given their skill as well as their
  opponent's and both players' career matches. It uses 538's formula for k. The
  only difference between this function and CalculateElo is that it accepts
  starting Elo values.
}
\arguments{
  \item{winner_names}{String vector of names of match winners}
  \item{loser_names}{String vector of names of match losers}
  \item{winner_match}{Numeric vector of career matches played by match winner}
  \item{loser_match}{Numeric vector of career matches played by match loser}
  \item{slam_factor}{Numeric vector to incorporate slam multiplier. This
    pre-multiplies the k factor; set equal to 1 to have no effect on rate.}
  \item{known_elo_names}{String vector of names for whom starting Elos are
    provided.}
  \item{known_elo_values}{Numeric vector of starting Elos for the players whose
    names are provided in "known_elo_names".}
}
\value{
  A list containing fields "winner_elo" and "loser_elo" containing the players'
  Elo ratings before the match update.
}
\usage{
  CalculateElo(winner_names, loser_names, winner_match, loser_match, slam_factor,
               known_elo_names, known_elo_values)
}
