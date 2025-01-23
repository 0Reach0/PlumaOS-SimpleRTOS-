
FROM ruby:latest


WORKDIR /app

COPY UnitTests/Tests .


RUN gem install ceedling


CMD ["ceedling", "test:all"]