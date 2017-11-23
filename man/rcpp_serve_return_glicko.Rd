\name{ServeReturnGlicko}
\alias{ServeReturnGlicko}
\docType{package}
\title{
Calculate serve and return Glicko adding match-to-match variance
}
\description{
  This function calculates a variant of Glicko designed to track serve and
  return skills over time. Rather than grouping data into periods, it updates
  after each point, adding variance after each match. If "backward_pass = TRUE",
  a backward pass is run over the data as described in the original Glicko
  paper.

  Please note that the vectors used as arguments must be sorted by date.
}
\arguments{
  \item{server}{A vector of strings containing the servers' names.}
  \item{returner}{A vector of strings containing the returners' names.}
  \item{server_won}{A vector of booleans representing whether the server won the
    current point or not.}
  \item{match_number}{An integer identifying the current match uniquely. For
    example, the first match could have match_number 0, the second 1, and so
    on.}
  \item{match_to_match_variance}{The variance to add between matches.}
  \item{initial_variance}{The initial variance of serve and return skills.}
  \item{initial_return_rating}{The initial return rating for previously unseen
    players.}
  \item{backward_pass}{Whether or not to perform the backward pass smoothing
    previous values.}
}
\value{
  A list containing fields "serve_mu" and "serve_sigma_sq" which represent the
  means and variances of the current server's serve skill, as well as
  "return_mu" and "return_sigma_sq", which represent the same quantities for the
  current returner's return skill.
}
\usage{
ServeReturnGlicko(server, returner, server_won, match_number,
                  match_to_match_variance, initial_variance,
                  initial_return_rating = 1410., backward_pass = FALSE)
}
\references{
  The Glicko paper: \url{http://www.glicko.net/research/glicko.pdf}
}
\examples{
\dontrun{
ServeReturnGlicko(server = c('Roger Federer', 'Roger Federer'),
                  returner = c('Rafael Nadal', 'Rafael Nadal'),
                  server_won = c(TRUE, TRUE),
                  match_number = c(0, 0),
                  match_to_match_variance = 32.,
                  initial_variance = 800.,
                  initial_return_rating = 1410.,
                  backward_pass = TRUE)
}
}
